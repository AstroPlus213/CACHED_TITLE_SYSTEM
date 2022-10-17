// Add :
// You know the drill

#ifdef ENABLE_TITLE_SYSTEM
	HEADER_CG_PLAYER_SET_TITLE = 207,
#endif

#ifdef ENABLE_TITLE_SYSTEM
	HEADER_GC_PLAYER_TITLES = 212,
#endif

// Before :

 } TPacketGCCharacterAdditionalInfo;
 
// Add :

#ifdef ENABLE_TITLE_SYSTEM
	DWORD dwTitleID;
#endif

// Before :

 } TPacketGCCharacterAdd2;	// Not used

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	DWORD dwTitleID;
#endif

// Before :

 } TPacketGCCharacterUpdate;

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	DWORD dwTitleID;
#endif

// Before :

 } TPacketGCCharacterUpdate2;	// Not used
 
// Add :

#ifdef ENABLE_TITLE_SYSTEM
	DWORD dwTitleID;
#endif

// At the end before #pragma pack() add :

#ifdef ENABLE_TITLE_SYSTEM
typedef struct SPacketGCPlayerTitles
{
	BYTE bHeader;
	DWORD dwTitleID;
}TPacketGCPlayerTitles;

typedef struct SPacketCGPlayerSetTitle
{
	BYTE bHeader;
	DWORD dwTitleID;
}TPacketCGPlayerSetTitle;
#endif
