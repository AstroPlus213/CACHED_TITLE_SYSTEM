// Inside CHARACTER::Initialize()
// Add :

#ifdef ENABLE_TITLE_SYSTEM
	m_vecTitles.clear();
#endif

// Inside void CHARACTER::EncodeInsertPacket(LPENTITY entity)
// After :

 			addPacket.sAlignment = m_iAlignment / 10;

// Add :

#ifdef ENABLE_TITLE_SYSTEM
			addPacket.dwTitleID = m_pointsInstant.dwTitleID;
#endif

// Inside void CHARACTER::UpdatePacket()
// After :

 	pack.bPKMode	= m_bPKMode;

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	pack.dwTitleID	= m_pointsInstant.dwTitleID;
#endif

// Inside void CHARACTER::CreatePlayerProto(TPlayerTable & tab)
// After :

 	tab.horse = GetHorseData();

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	tab.dwTitleID = m_pointsInstant.dwTitleID;
#endif

// Inside void CHARACTER::SetPlayerProto(const TPlayerTable * t)
// After :

 	m_petSystem = M2_NEW CPetSystem(this);
 #endif
 
// Add :

#ifdef ENABLE_TITLE_SYSTEM
	m_pointsInstant.dwTitleID = t->dwTitleID;
#endif

// Add at the end :


#ifdef ENABLE_TITLE_SYSTEM
void CHARACTER::LoadTitle(DWORD dwCount, TPlayerTitle* pElements)
{
	if (!m_vecTitles.empty())
	{
		sys_err("titles are already loaded.");
		return;
	}

	// For optimization
	/*m_vecTitles.resize(dwCount);
	for (DWORD i = 0; i < dwCount; ++i, ++pElements)
	{
		DWORD dwTitleID = pElements->dwTitleID;
		m_vecTitles.emplace_back(dwTitleID);
	}*/

	for (DWORD i = 0; i < dwCount; ++i, ++pElements)
	{
		DWORD dwTitleID = pElements->dwTitleID;
		m_vecTitles.push_back(dwTitleID);
	}

	// TODO: We need to send the list to the player in CInputLogin::EnterGame
}

bool CHARACTER::FindTitle(DWORD dwTitleID)
{
	// Advanced
	/*return std::find(m_vecTitles.begin(), m_vecTitles.end(), dwTitleID) != m_vecTitles.end();*/

	for(size_t i = 0; i < m_vecTitles.size(); ++i)
	{
		if (m_vecTitles.at(i) == dwTitleID)
			return true;
	}
	return false;
}

bool CHARACTER::AddTitle(DWORD dwTitleID)
{
	if (FindTitle(dwTitleID))
		return false;

	TTitleTable* pTitle = GetTitleByID(dwTitleID);
	if (!pTitle)
	{
		sys_err("TITLE_SYSTEM: the selected title doesn't exist.");
		return false;
	}

	// Add title 
	m_vecTitles.push_back(dwTitleID);

	TPlayerTitle p;
	p.dwPlayerID = GetPlayerID();
	p.dwTitleID = dwTitleID;
	db_clientdesc->DBPacket(HEADER_GD_ADD_TITLE, 0, &p, sizeof(p));
	return true;
}

bool CHARACTER::RemoveTitle(DWORD dwTitleID)
{
	if (!FindTitle(dwTitleID))
		return false;

	TTitleTable* pTitle = GetTitleByID(dwTitleID);
	if (!pTitle)
	{
		sys_err("TITLE_SYSTEM: the selected title doesn't exist.");
		return false;
	}

	// Add title
	const auto& it = std::find(m_vecTitles.begin(), m_vecTitles.end(), dwTitleID);
	m_vecTitles.erase(it);

	TPlayerTitle p;
	p.dwPlayerID = GetPlayerID();
	p.dwTitleID = dwTitleID;
	db_clientdesc->DBPacket(HEADER_GD_REMOVE_TITLE, 0, &p, sizeof(p));
	return true;
}

void CHARACTER::SetTitle(DWORD dwTitleID)
{
	// Find title
	if (!FindTitle(dwTitleID))
		return;

	// Get title table
	TTitleTable* pTitle = GetTitleByID(dwTitleID);
	if (!pTitle)
		return;

	// Remove old bonuses
	CAffect* pAffect = FindAffect(AFFECT_TITLE_BONUS);
	if (pAffect)
		RemoveAffect(pAffect);

	// Set title
	m_pointsInstant.dwTitleID = dwTitleID;

	// Add the new bonuses.
	AddAffect(AFFECT_TITLE_BONUS, aApplyInfo[pTitle->attr.bType].bPointType, pTitle->attr.sValue, 0, INFINITE_AFFECT_DURATION, 0, false, 0);

	// If the bonuses is an array
	/*for(int i = 0; i < PLAYER_TITLE_ATTR_MAX_NUM; ++i)
	{
		AddAffect(AFFECT_TITLE_BONUS, aApplyInfo[pTitle->attr[i].bType].bPointType, pTitle->attr[i].sValue, 0, INFINITE_AFFECT_DURATION, 0, false, 0);
	}*/


	// TODO: Send the new title to the client.
	UpdatePacket();
}

void CHARACTER::SendTitles()
{
	TPacketGCPlayerTitles pack;
	pack.bHeader = HEADER_GC_PLAYER_TITLES;
	for(const auto & it : m_vecTitles)
	{
		pack.dwTitleID = it;
		// sys_err("SENDTITLES: PLAYER TITLE %d", pack.dwTitleID);
		GetDesc()->Packet(&pack, sizeof(TPacketGCPlayerTitles));
	}
}
#endif
