// Inside bool CPythonNetworkStream::RecvCharacterAppendPacket()
// After :

 	kNetActorData.m_dwLevel = 0;

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	kNetActorData.m_dwTitleID = 0;
#endif

// Inside bool CPythonNetworkStream::RecvCharacterAdditionalInfo()
// After :

 		kNetActorData.m_dwMountVnum	= chrInfoPacket.dwMountVnum;

// Add :

#ifdef ENABLE_TITLE_SYSTEM
		kNetActorData.m_dwTitleID = chrInfoPacket.dwTitleID;
#endif

// Inside bool CPythonNetworkStream::RecvCharacterUpdatePacket()
// After :

 	kNetUpdateActorData.m_dwMountVnum=chrUpdatePacket.dwMountVnum;

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	kNetUpdateActorData.m_dwTitleID = chrUpdatePacket.dwTitleID;
#endif

