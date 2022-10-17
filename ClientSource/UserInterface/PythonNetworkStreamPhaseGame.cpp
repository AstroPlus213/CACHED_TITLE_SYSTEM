// Inside void CPythonNetworkStream::GamePhase()
// Add :

#ifdef ENABLE_TITLE_SYSTEM
		case HEADER_GC_PLAYER_TITLES:
			ret = RecvCharacterTitles();
			break;
#endif

// Add :

#ifdef ENABLE_TITLE_SYSTEM
bool CPythonNetworkStream::SendPlayerSetTitlePacket(DWORD dwTitleID)
{
	TPacketCGPlayerSetTitle pack;
	pack.bHeader = HEADER_CG_PLAYER_SET_TITLE;
	pack.dwTitleID = dwTitleID;
	if (!Send(sizeof(pack), &pack))
		return false;

	return true;
}

bool CPythonNetworkStream::RecvCharacterTitles()
{
	TPacketGCPlayerTitles kPlayerTitles;
	if (!Recv(sizeof(TPacketGCPlayerTitles), &kPlayerTitles))
		return false;

	TTitleTable* pTitle = GetTitleByID(kPlayerTitles.dwTitleID);
	if (pTitle) {
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_SetPlayerTitle", Py_BuildValue("(is)", kPlayerTitles.dwTitleID, pTitle->szName));
	}
	// TraceError("title %s", pTitle ? pTitle->szName : "NoName");

	return true;
}
#endif