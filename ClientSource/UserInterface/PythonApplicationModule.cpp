// Add at the end and before }

#ifdef ENABLE_TITLE_SYSTEM
	PyModule_AddIntConstant(poModule, "ENABLE_TITLE_SYSTEM", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_TITLE_SYSTEM", 0);
#endif
