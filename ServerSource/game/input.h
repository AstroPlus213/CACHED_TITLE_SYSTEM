// Inside class CInputMain : public CInputProcessor
// Add :

#ifdef ENABLE_TITLE_SYSTEM
	void PlayerSetTitle(LPCHARACTER ch, const char* c_pData);
#endif

// After :

 	void RespondChannelStatus(LPDESC desc, const char* pcData);

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	void TitleLoad(LPDESC d, const char* c_pData);
#endif
