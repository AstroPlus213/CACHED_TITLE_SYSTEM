// Inside void CInputLogin::Entergame(LPDESC d, const char * data)
// Add :

#ifdef ENABLE_TITLE_SYSTEM
	// TODO: send all titles.
	ch->SendTitles();
#endif

