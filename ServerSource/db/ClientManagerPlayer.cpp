// Inside size_t CreatePlayerSaveQuery(char * pszQuery, size_t querySize, TPlayerTable * p :
// After :

 			"horse_skill_point = %d, "

// Add :

#ifdef ENABLE_TITLE_SYSTEM
			"title_id = %u,"
#endif

// After :

 		pkTab->horse.sStamina,
		pkTab->horse_skill_point);

// Make the needed changes :

		pkTab->horse_skill_point
#ifdef ENABLE_TITLE_SYSTEM
		,pkTab->dwTitleID
#endif
	);

// Inside void CClientManager::QUERY_PLAYER_LOAD(CPeer * peer, DWORD dwHandle, TPlayerLoad:
// After :

				"UNIX_TIMESTAMP(NOW())-UNIX_TIMESTAMP(last_play),horse_skill_point

// Make the needed changes :

				"UNIX_TIMESTAMP(NOW())-UNIX_TIMESTAMP(last_play),horse_skill_point"
#ifdef ENABLE_TITLE_SYSTEM
				", title_id"
#endif
				" FROM player%s WHERE id=%d",

// Inside bool CreatePlayerTableFromRes(MYSQL_RES :
// After :

 	str_to_number(pkTab->horse_skill_point, row[col++]);

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	str_to_number(pkTab->dwTitleID, row[col++]);
#endif

// Inside void CClientManager::RESULT_COMPOSITE_PLAYER(CPeer * peer, SQLMsg * pMsg, DWORD :
// After :

 			RESULT_AFFECT_LOAD(peer, pSQLResult, info->dwHandle, info->player_id);
 			break;

// Add :

#ifdef ENABLE_TITLE_SYSTEM
		case QID_TITLE:
			// sys_log(0, "QID_TITLE %u", info->dwHandle);
			RESULT_TITLE_LOAD(peer, pSQLResult, info->dwHandle, info->player_id);
			break;
#endif

// Before :

 }
 void CClientManager::ItemAward(CPeer * peer,char* login)
 {

// So the addition would be inside void CClientManager::QUERY_PLAYER_LOAD before the last }
// Add :
 
#ifdef ENABLE_TITLE_SYSTEM
#ifdef ENABLE_TITLE_SYSTEM_CACHE
	TPlayerTitleCache* pTitleCache = GetPlayerTitleCacheMap(packet->player_id);
	if (pTitleCache && c)
	{
		// Send packet to game.
		sys_log(0, "LoadPlayerTitleFromCache pid %u", packet->player_id);

		std::vector<TPlayerTitle> vecTitles; 
		for(TPlayerTitleCache::const_iterator it = pTitleCache->begin(); it != pTitleCache->end(); ++it)
		{
			vecTitles.push_back(*it->second->Get());
		}

		DWORD dwPID = packet->player_id;
		DWORD dwCount = vecTitles.size();
		peer->EncodeHeader(HEADER_DG_TITLE_LOAD, dwHandle, sizeof(DWORD) + sizeof(DWORD) + sizeof(TPlayerTitle) * dwCount);
		peer->Encode(&dwPID, sizeof(DWORD));
		peer->Encode(&dwCount, sizeof(DWORD));
		peer->Encode(&vecTitles[0], sizeof(TPlayerTitle)* dwCount);
	}
	else
	{
		char szQuery[QUERY_MAX_LEN];
		snprintf(szQuery, sizeof(szQuery), "SELECT id FROM player_title%s WHERE pid=%d", GetTablePostfix(), packet->player_id);
		CDBManager::instance().ReturnQuery(szQuery, QID_TITLE, peer->GetHandle(), new ClientHandleInfo(dwHandle, packet->player_id));
	}
#else
	char szQuery[QUERY_MAX_LEN];
	snprintf(szQuery, sizeof(szQuery), "SELECT id FROM player_title%s WHERE pid=%d", GetTablePostfix(), packet->player_id);
	CDBManager::instance().ReturnQuery(szQuery, QID_TITLE, peer->GetHandle(), new ClientHandleInfo(dwHandle, packet->player_id));
#endif
#endif

// At the end add :


#ifdef ENABLE_TITLE_SYSTEM
void CClientManager::RESULT_TITLE_LOAD(CPeer* peer, MYSQL_RES* pRes, DWORD dwHandle, DWORD dwRealPID)
{
	int iNumRows;

	if ((iNumRows = mysql_num_rows(pRes)) == 0)
	{
		static DWORD dwPID = dwRealPID;
		static DWORD dwCount = 0; //1;
		static TPlayerTitle paeTable = { 0 };

		dwPID = dwRealPID;
		sys_log(0, "TITLE_LOAD: count %u PID %u RealPID %u", dwCount, dwPID, dwRealPID);

		peer->EncodeHeader(HEADER_DG_TITLE_LOAD, dwHandle, sizeof(DWORD) + sizeof(DWORD) + sizeof(TPlayerTitle) * dwCount);
		peer->Encode(&dwPID, sizeof(DWORD));
		peer->Encode(&dwCount, sizeof(DWORD));
		peer->Encode(&paeTable, sizeof(TPlayerTitle) * dwCount);
		return;
	}

	static std::vector<TPlayerTitle> s_elements;
	s_elements.resize(iNumRows);

	DWORD dwPID = dwRealPID;

	MYSQL_ROW row;

	for (int i = 0; i < iNumRows; ++i)
	{
		TPlayerTitle& r = s_elements[i];
		r.dwPlayerID = dwPID;
		row = mysql_fetch_row(pRes);
		str_to_number(r.dwTitleID, row[0]);
	}

#ifdef ENABLE_TITLE_SYSTEM_CACHE
	for (size_t i = 0; i < s_elements.size(); ++i)
		PutPlayerTitleCache(dwPID, &s_elements[i]);
#endif
	sys_log(0, "TITLE_LOAD: count %d PID %u", s_elements.size(), dwPID);

	DWORD dwCount = s_elements.size();

	peer->EncodeHeader(HEADER_DG_TITLE_LOAD, dwHandle, sizeof(DWORD) + sizeof(DWORD) + sizeof(TPlayerTitle) * dwCount);
	peer->Encode(&dwPID, sizeof(DWORD));
	peer->Encode(&dwCount, sizeof(DWORD));
	peer->Encode(&s_elements[0], sizeof(TPlayerTitle) * dwCount);
}

void CClientManager::QUERY_ADD_TITLE(CPeer* peer, TPlayerTitle* p)
{
#ifdef ENABLE_TITLE_SYSTEM_CACHE
	CPlayerTitleCache* c = GetPlayerTitleCache(p->dwPlayerID, p->dwTitleID);
	if (!c)
	{
		PutPlayerTitleCache(p->dwPlayerID, p);
	}
	else
	{
		char queryStr[QUERY_MAX_LEN];
		snprintf(queryStr, sizeof(queryStr), "REPLACE INTO player_title%s (pid, id) VALUES(%u, %u)", GetTablePostfix(), p->dwPlayerID, p->dwTitleID);
		CDBManager::instance().AsyncQuery(queryStr);
	}
#else
	char queryStr[QUERY_MAX_LEN];
	snprintf(queryStr, sizeof(queryStr), "REPLACE INTO player_title%s (pid, id) VALUES(%u, %u)", GetTablePostfix(), p->dwPlayerID, p->dwTitleID);
	CDBManager::instance().AsyncQuery(queryStr);
#endif
}

void CClientManager::QUERY_REMOVE_TITLE(CPeer * peer, TPlayerTitle * p)
{
#ifdef ENABLE_TITLE_SYSTEM_CACHE
	CPlayerTitleCache* c = GetPlayerTitleCache(p->dwPlayerID, p->dwTitleID);
	if (c)
	{
		c->SetDeleted();
		c->OnFlush();
		// sys_log(0, "QUERY_REMOVE_TITLE cache pid %u title %u", p->dwPlayerID, p->dwTitleID);
	}
	else
	{
		char queryStr[QUERY_MAX_LEN];
		snprintf(queryStr, sizeof(queryStr), "DELETE FROM player_title%s WHERE pid=%u AND id=%u", GetTablePostfix(), p->dwPlayerID, p->dwTitleID);
		CDBManager::instance().AsyncQuery(queryStr);
	}
#else
	char queryStr[QUERY_MAX_LEN];
	snprintf(queryStr, sizeof(queryStr), "DELETE FROM player_title%s WHERE pid=%u AND id=%u", GetTablePostfix(), p->dwPlayerID, p->dwTitleID);
	CDBManager::instance().AsyncQuery(queryStr);
#endif
#endif
