// At the end add :

#ifdef ENABLE_TITLE_SYSTEM
public:
	bool SendPlayerSetTitlePacket(DWORD dwTitleID);
	bool RecvCharacterTitles();
#endif
