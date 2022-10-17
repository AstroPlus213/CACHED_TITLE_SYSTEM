// Before :

 			bool	m_isMain;
 		};

// Add :

#ifdef ENABLE_TITLE_SYSTEM
			DWORD	m_dwTitleID;
#endif

// After :

 		void					RegisterBoundingSphere();

// Add :

#ifdef ENABLE_TITLE_SYSTEM
		void					SetTitleID(DWORD dwTitleID);
		std::string				GetTitleNameString();
		D3DXCOLOR*				GetPlayerTitleColor();
#endif

// After :

 		bool					m_isPartyMember;

// Add :

#ifdef ENABLE_TITLE_SYSTEM
		DWORD					m_dwTitleID;
#endif


