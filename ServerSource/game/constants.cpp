// Add :

#ifdef ENABLE_TITLE_SYSTEM
enum ETitleMisc
{
	PLAYER_TITLE_MAX_NUM = 4,
};

// This must match the client's array @ UserInterface/GameType.h
TTitleTable aTitles[PLAYER_TITLE_MAX_NUM] = 
{
	{
		1, "Life", {APPLY_MAX_HP, 1000}
		//, D3DXCOLOR(0.8f, 0.3f, 0.1f, 1.0f)
	},
	{
		2, "Mana", {APPLY_MAX_SP, 1000}
		//, D3DXCOLOR(0.1f, 0.3f, 0.8f, 1.0f)
	},
	{
		3, "Attck", {APPLY_ATT_GRADE_BONUS, 1000}
		//, D3DXCOLOR(0.9f, 0.5f, 0.4f, 1.0f)
	},
	{
		4, "Defense", {APPLY_DEF_GRADE_BONUS, 1000}
		//, D3DXCOLOR(0.3f, 0.8f, 0.2f, 1.0f)
	},
};

TTitleTable* GetTitleByID(DWORD dwTitleID)
{
	for (size_t i = 0; i < _countof(aTitles); ++i)
		if (aTitles[i].dwID == dwTitleID)
			return &aTitles[i];
	return nullptr;
}
#endif
