// Inside void CClientManager::QUERY_FLUSH_CACHE :
// After :

 	FlushItemCacheSet(dwPID);

// Add :

#ifdef ENABLE_TITLE_SYSTEM_CACHE
	FlushPlayerTitleCache(dwPID);
#endif

// Inside void CClientManager::ProcessPackets :
// Before :

 			default:
 				sys_err("Unknown header (header: %d handle: %d length: %d)", header, dwHandle, dwLength);

// Add :

#ifdef ENABLE_TITLE_SYSTEM
			case HEADER_GD_ADD_TITLE:
				// sys_log(1, "HEADER_GD_ADD_TITLE");
				QUERY_ADD_TITLE(peer, (TPlayerTitle*)data);
				break;
			case HEADER_GD_REMOVE_TITLE:
				// sys_log(1, "HEADER_GD_REMOVE_TITLE");
				QUERY_REMOVE_TITLE(peer, (TPlayerTitle*)data);
				break;
#endif

// Inside int CClientManager::AnalyzeQueryResult(SQLMsg * msg) :
// After :

 		case QID_AFFECT:

// Add :

#ifdef ENABLE_TITLE_SYSTEM
		case QID_TITLE:
#endif

// Inside int CClientManager::Process() :
// After :

 			UpdateLogoutPlayer();

// Add :

#ifdef ENABLE_TITLE_SYSTEM_CACHE
			UpdatePlayerTitleCache();
#endif

// At the end add :


#ifdef ENABLE_TITLE_SYSTEM_CACHE
CClientManager::TPlayerTitleCache * CClientManager::GetPlayerTitleCacheMap(DWORD dwPID)
{
	const auto& it = m_map_playerTitleCachePtr.find(dwPID);
	if (it == m_map_playerTitleCachePtr.end())
		return nullptr;

	sys_log(0, "GetPlayerTitleCacheMap Get pid %u ", dwPID);
	return &it->second;
}

void CClientManager::PutPlayerTitleCache(DWORD dwPID, TPlayerTitle *title)
{
	const auto& it = m_map_playerTitleCachePtr.find(dwPID);
	// If the key exists
	if (it != m_map_playerTitleCachePtr.end())
	{
		const auto& iter = it->second.find(title->dwTitleID);
		if (iter != it->second.end())
		{
			// Update cache
			sys_log(0, "PutPlayerTitleCache update pid %u title %u", dwPID, title->dwTitleID);

			iter->second->Put(title);
			return;
		}
		// Add new cache
		CPlayerTitleCache* newCache = new CPlayerTitleCache;

		newCache->Put(title);
		sys_log(0, "PutPlayerTitleCache append pid %u title %u", dwPID, title->dwTitleID);

		it->second.insert(std::make_pair(title->dwTitleID, newCache));
		return;
	}
	// The key doesn't exist
	CPlayerTitleCache* newCache = new CPlayerTitleCache;

	newCache->Put(title);

	TPlayerTitleCache cacheMap;
	cacheMap.insert(std::make_pair(title->dwTitleID, newCache));
	sys_log(0, "PutPlayerTitleCache add pid %u title %u", dwPID, title->dwTitleID);

	// Now we need to add this map to the map that has pid as a key.
	m_map_playerTitleCachePtr.insert(std::make_pair(dwPID, cacheMap));
}

void CClientManager::UpdatePlayerTitleCache(DWORD dwPID, TPlayerTitle title)
{
	const auto& it = m_map_playerTitleCachePtr.find(dwPID);
	// If the key doesn't exist
	if (it == m_map_playerTitleCachePtr.end())
		return;

	const auto& iter = it->second.find(title.dwTitleID);
	if (iter == it->second.end())
		return;

	sys_log(0, "UpdatePlayerTitleCache pid %u title %u", dwPID, title.dwTitleID);
	iter->second->Put(&title);
}

void CClientManager::UpdatePlayerTitleCache()
{
	for(const auto & it : m_map_playerTitleCachePtr)
	{
		for(const auto & iter : it.second)
		{
			CPlayerTitleCache* c = iter.second;
			if (!c)
				continue;

			if (c->CheckTimeout())
			{
				if (g_log)
					sys_log(0, "UPDATE : UpdateTitleCache() ==> FlushTitleCache %d %d ", c->Get(false)->dwPlayerID, c->Get(false)->dwTitleID);

				c->Flush();
			}
			else if (c->CheckFlushTimeout())
				c->Flush();
		}
	}
}

void CClientManager::FlushPlayerTitleCache(DWORD dwPID)
{
	const auto& it = m_map_playerTitleCachePtr.find(dwPID);
	if (it == m_map_playerTitleCachePtr.end())
		return;

	sys_log(0, "FlushPlayerTitleCache pid %u", dwPID);

	for(const auto & iter : it->second)
	{
		CPlayerTitleCache* c = iter.second;
		if (!c)
			continue;

		c->Flush();
		it->second.erase(iter.first);
		delete c;
	}
}

CPlayerTitleCache * CClientManager::GetPlayerTitleCache(DWORD dwPID, DWORD dwTitleID)
{
	const auto& it = m_map_playerTitleCachePtr.find(dwPID);
	if (it == m_map_playerTitleCachePtr.end())
		return nullptr;

	const auto& iter = it->second.find(dwTitleID);
	if (iter == it->second.end())
		return nullptr;

	sys_log(0, "GetPlayerTitleCache pid %u title %u", dwPID, dwTitleID);
	return iter->second;
}
#endif
