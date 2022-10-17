// Add :

#ifdef ENABLE_TITLE_SYSTEM_CACHE
CPlayerTitleCache::CPlayerTitleCache()
{
}

CPlayerTitleCache::~CPlayerTitleCache()
{
}

void CPlayerTitleCache::OnFlush()
{
	char szQuery[QUERY_MAX_LEN];
	if (m_bMarkDeleted)
	{
		snprintf(szQuery, sizeof(szQuery), "DELETE FROM player_title%s WHERE pid = %u AND id=%u", GetTablePostfix(), m_data.dwPlayerID, m_data.dwTitleID);
		CDBManager::instance().AsyncQuery(szQuery);
		return;
	}
	snprintf(szQuery, sizeof(szQuery), "REPLACE INTO player_title%s SET pid = %u, id=%u", GetTablePostfix(), m_data.dwPlayerID, m_data.dwTitleID);
	CDBManager::instance().AsyncQuery(szQuery);
}
#endif
