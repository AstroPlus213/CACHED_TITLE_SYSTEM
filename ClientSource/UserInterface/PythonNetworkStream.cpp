// Inside class CMainPacketHeaderMap : public CNetworkPacketHeaderMap
// Add :

#ifdef ENABLE_TITLE_SYSTEM
		Set(HEADER_GC_PLAYER_TITLES, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCPlayerTitles), STATIC_SIZE_PACKET));
#endif
