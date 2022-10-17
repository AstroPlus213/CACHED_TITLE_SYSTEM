// Inside struct SNetworkActorData
// After :

 	DWORD	m_dwLevel;

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	DWORD	m_dwTitleID;
#endif

// Inside struct SNetworkUpdateActorData
// After :

 	DWORD m_dwStateFlags;

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	DWORD m_dwTitleID;
#endif

// Inside struct SNetworkUpdateActorData
// After :

 		m_dwStateFlags=0;

// Add :

#ifdef ENABLE_TITLE_SYSTEM
		m_dwTitleID = 0;
#endif
