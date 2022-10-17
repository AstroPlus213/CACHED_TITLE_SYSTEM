#ifdef ENABLE_TITLE_SYSTEM
ACMD(do_set_title)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!arg1)
		return;

	DWORD dwTitleID = 0;
	str_to_number(dwTitleID, arg1);

	if (!dwTitleID)
		return;

	// Find the title
	if (!ch->FindTitle(dwTitleID))
		if (!ch->AddTitle(dwTitleID))
			return;

	ch->SetTitle(dwTitleID);
	ch->ChatPacket(CHAT_TYPE_INFO, "Title %u has been set.", dwTitleID);
}

ACMD(do_remove_title)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!arg1)
		return;

	DWORD dwTitleID = 0;
	str_to_number(dwTitleID, arg1);

	if (!dwTitleID)
		return;

	// Find the title
	if (!ch->FindTitle(dwTitleID))
		return;

	ch->RemoveTitle(dwTitleID);
	ch->ChatPacket(CHAT_TYPE_INFO, "Title %u has been removed.", dwTitleID);
	ch->UpdatePacket();
}

ACMD(do_titles_list)
{
	auto vecTitles = ch->GetTitlesVec();
	if (vecTitles.empty())
		return;

	ch->ChatPacket(CHAT_TYPE_INFO, "Titles count: %d", vecTitles.size());
	TTitleTable* pTitle = nullptr;
	for (const auto& it : vecTitles)
	{
		pTitle = GetTitleByID(it);
		if (!pTitle)
			continue;

		ch->ChatPacket(CHAT_TYPE_INFO, "Title: %s", pTitle->szName);
	}
}
#endif
