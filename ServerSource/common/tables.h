// After :

 	HEADER_GD_GUILD_WAR_BET = 57,

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	HEADER_GD_ADD_TITLE = 58,
	HEADER_GD_REMOVE_TITLE = 59,
#endif

// After :

 	HEADER_DG_RESPOND_CHANNELSTATUS = 181,

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	HEADER_DG_TITLE_LOAD = 182,
#endif

// After :

 	int		aiPremiumTimes[PREMIUM_MAX_NUM];

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	DWORD	dwTitleID;
#endif

// After :

 } TChannelStatus;
 
 // Add :
#ifdef ENABLE_TITLE_SYSTEM
typedef struct SPlayerTitle
{
	DWORD dwPlayerID;
	DWORD dwTitleID;
}TPlayerTitle;

typedef struct STitleTable
{
	DWORD dwID;
	const char* szName;
	TPlayerItemAttribute attr;
}TTitleTable;
#endif

