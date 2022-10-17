// Add :

    ALUA(pc_add_title)
    {
        if (lua_isnumber(L, 1))
        {
            CQuestManager& qMgr = CQuestManager::instance();
            LPCHARACTER ch = qMgr.GetCurrentCharacterPtr();
            if (ch)
                ch->AddTitle(lua_toboolean(L, 1));
        }
        else
            sys_err("Invalid argument: arg1 must be boolean.");

        return 0;
    }

// Add :

