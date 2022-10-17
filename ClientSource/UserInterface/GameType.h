// After :

 BYTE SlotTypeToInvenType(BYTE bSlotType);

// Add :

#ifdef ENABLE_TITLE_SYSTEM
typedef struct STitleTable
{
	DWORD dwTitleID;
	const char* szName;
	TPlayerItemAttribute attr;
	D3DXCOLOR color;
}TTitleTable;

TTitleTable* GetTitleByID(DWORD dwTitleID);
#endif
