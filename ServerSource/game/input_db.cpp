// After :

 	case HEADER_DG_RESPOND_CHANNELSTATUS:
 		RespondChannelStatus(DESC_MANAGER::instance().FindByHandle(m_dwHandle), c_pData);
 		break;

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	case HEADER_DG_TITLE_LOAD:
		TitleLoad(DESC_MANAGER::instance().FindByHandle(m_dwHandle), c_pData);
		break;
#endif

// Before ::Analyse
// Add :

#ifdef ENABLE_TITLE_SYSTEM
void CInputDB::TitleLoad(LPDESC d, const char* c_pData)
{
	if (!d)
		return;

	if (!d->GetCharacter())
		return;

	LPCHARACTER ch = d->GetCharacter();

	DWORD dwPID = decode_4bytes(c_pData);
	c_pData += sizeof(DWORD);

	DWORD dwCount = decode_4bytes(c_pData);
	c_pData += sizeof(DWORD);

	if (ch->GetPlayerID() != dwPID)
		return;

	if (!dwCount)
		return;

	ch->LoadTitle(dwCount, (TPlayerTitle*)c_pData);
}
#endif
