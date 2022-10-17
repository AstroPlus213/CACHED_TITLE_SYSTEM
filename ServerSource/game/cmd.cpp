// Add :

#ifdef ENABLE_TITLE_SYSTEM
ACMD(do_set_title);
ACMD(do_remove_title);
ACMD(do_titles_list);
#endif

#ifdef ENABLE_TITLE_SYSTEM
	{ "set_title", do_set_title, 0, POS_DEAD, GM_PLAYER },
	{ "remove_title", do_remove_title, 0, POS_DEAD, GM_PLAYER },
	{ "titles_list", do_titles_list, 0, POS_DEAD, GM_PLAYER },
#endif
 