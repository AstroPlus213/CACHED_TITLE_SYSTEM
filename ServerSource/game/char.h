// Inside typedef struct character_point_instant:
// Before :

 } CHARACTER_POINT_INSTANT;
 
// Add :

#ifdef ENABLE_TITLE_SYSTEM
	DWORD			dwTitleID;
#endif

// At the end before 

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	private:
		std::vector<DWORD>	m_vecTitles;

	public:
		void LoadTitle(DWORD dwCount, TPlayerTitle* pElements);
		bool FindTitle(DWORD dwTitleID);

		bool AddTitle(DWORD dwTitleID);
		bool RemoveTitle(DWORD dwTitleID);

		void SetTitle(DWORD dwTitleID);
		void SendTitles();

		DWORD GetTitle() { return m_pointsInstant.dwTitleID; }
		std::vector<DWORD>& GetTitlesVec() { return m_vecTitles; }
#endif