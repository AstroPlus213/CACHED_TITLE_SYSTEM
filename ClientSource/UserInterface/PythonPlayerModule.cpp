// Add :

#ifdef ENABLE_TITLE_SYSTEM
PyObject* playerGetPlayerTitle(PyObject* poSelf, PyObject* poArgs)
{
	int titleID = 0;
	if (!PyTuple_GetInteger(poArgs, 0, &titleID))
		return Py_BadArgument();

	TTitleTable* pTitle = GetTitleByID(titleID);
	if (!pTitle)
		return Py_BadArgument();

	return Py_BuildValue("siiffff", pTitle->szName, pTitle->attr.bType, pTitle->attr.sValue,
							pTitle->color.r, pTitle->color.g, pTitle->color.b, pTitle->color.a);
}
#endif

#ifdef ENABLE_TITLE_SYSTEM
		{ "GetPlayerTitle", playerGetPlayerTitle, METH_VARARGS},
#endif
