// Inside void CInstanceBase::RefreshTextTail()
// After :

 			CPythonTextTail::Instance().AttachTitle(GetVirtualID(), c_rstrTitleName.c_str(), GetTitleColor());
 		}
 	}

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	if (m_dwTitleID == 0)
		CPythonTextTail::Instance().DetachPlayerTitle(GetVirtualID());
	else
	{
		TTitleTable* pTitle = GetTitleByID(m_dwTitleID);
		if (pTitle)
		{
			const std::string& c_rstrTitleName = /*"[" + */std::string(pTitle->szName)/* + "]"*/;
			CPythonTextTail::Instance().AttachPlayerTitle(GetVirtualID(), c_rstrTitleName.c_str(), 
				pTitle->color);
		}
	}
#endif
