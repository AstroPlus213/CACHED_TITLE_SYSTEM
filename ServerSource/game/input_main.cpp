// Before :

int CInputMain::Analyze(LPDESC d, BYTE bHeader, const char * c_pData)

// Add :

#ifdef ENABLE_TITLE_SYSTEM
void CInputMain::PlayerSetTitle(LPCHARACTER ch, const char* c_pData)
{
	TPacketCGPlayerSetTitle* p = (TPacketCGPlayerSetTitle*)c_pData;
	if (!p->dwTitleID)
		return;

	ch->SetTitle(p->dwTitleID);
}
#endif

// Inside int CInputMain::Analyze(LPDESC d, BYTE bHeader, const char * c_pData)
// Add :

#ifdef ENABLE_TITLE_SYSTEM
		case HEADER_CG_PLAYER_SET_TITLE:
			PlayerSetTitle(ch, c_pData);
			break;
#endif

