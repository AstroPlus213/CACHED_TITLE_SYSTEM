// Inside void SNetworkActorData::__copy__(const SNetworkActorData& src)
// After :

 	m_stName = src.m_stName;

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	m_dwTitleID = src.m_dwTitleID;
#endif

// Inside SNetworkActorData::SNetworkActorData()
// After :

 	m_stName="";

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	m_dwTitleID = 0;
#endif

// Inside CInstanceBase* CNetworkActorManager::__AppendCharacterManagerActor(SNetworkActor
// After :

 	kCreateData.m_isMain=__IsMainActorVID(dwVID);
 
// Add :

#ifdef ENABLE_TITLE_SYSTEM
	kCreateData.m_dwTitleID = rkNetActorData.m_dwTitleID;
#endif

// Inside void CNetworkActorManager::UpdateActor(const SNetworkUpdateActorData& c_rkNetUpd
// After :

 		pkInstFind->SetStateFlags(c_rkNetUpdateActorData.m_dwStateFlags);

// Add :

#ifdef ENABLE_TITLE_SYSTEM
		pkInstFind->SetTitleID(c_rkNetUpdateActorData.m_dwTitleID);
#endif

// Inside void CNetworkActorManager::UpdateActor(const SNetworkUpdateActorData& c_rkNetUpd
// After :

 	rkNetActorData.m_byPKMode=c_rkNetUpdateActorData.m_byPKMode;

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	rkNetActorData.m_dwTitleID = c_rkNetUpdateActorData.m_dwTitleID;
#endif
