// After :

class CItemPriceListTableCache;

// Add :

#ifdef ENABLE_TITLE_SYSTEM
class CPlayerTitleCache;
#endif

// After :

 	typedef boost::unordered_map<short, BYTE> TChannelStatusMap;

// Add :

#ifdef ENABLE_TITLE_SYSTEM_CACHE
	typedef boost::unordered_map<DWORD, CPlayerTitleCache*> TPlayerTitleCache;
	typedef boost::unordered_map<DWORD, TPlayerTitleCache> TPlayerTitleCacheMap;
#endif

// After :

 	void		ChargeCash(const TRequestChargeCash * p);

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	void		RESULT_TITLE_LOAD(CPeer* peer, MYSQL_RES* pRes, DWORD dwHandle, DWORD dwRealPID);

	TPlayerTitleCache* GetPlayerTitleCacheMap(DWORD dwPID);
	void		PutPlayerTitleCache(DWORD dwPID, TPlayerTitle *title);
	void		UpdatePlayerTitleCache(DWORD dwPID, TPlayerTitle title);
	void		UpdatePlayerTitleCache();
	void		FlushPlayerTitleCache(DWORD dwPID);
	CPlayerTitleCache* GetPlayerTitleCache(DWORD dwPID, DWORD dwTitleID);

	void QUERY_ADD_TITLE(CPeer* peer, TPlayerTitle* p);
	void QUERY_REMOVE_TITLE(CPeer* peer, TPlayerTitle* p);
#endif

// After :

 	TChannelStatusMap m_mChannelStatus;

// Add :

#ifdef ENABLE_TITLE_SYSTEM_CACHE
	TPlayerTitleCacheMap m_map_playerTitleCachePtr;
#endif

