// After :

 			CGraphicTextInstance*			pGuildNameTextInstance;

// Add :

#ifdef ENABLE_TITLE_SYSTEM
			CGraphicTextInstance*			pPlayerTitleTextInstance;
#endif

// After :

 		void AttachTitle(DWORD dwVID, const char * c_szName, const D3DXCOLOR& c_rColor);

// Add :

#ifdef ENABLE_TITLE_SYSTEM
		void AttachPlayerTitle(DWORD dwVID, const char* c_szName, const D3DXCOLOR& c_rColor = D3DXCOLOR());
		void DetachPlayerTitle(DWORD dwVID);
#endif

