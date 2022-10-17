// Inside PyObject * chrCreateInstance
// After :

 		kCreateData.m_isMain=false;

// Add :

#ifdef ENABLE_TITLE_SYSTEM
		kCreateData.m_dwTitleID = 0;
#endif

