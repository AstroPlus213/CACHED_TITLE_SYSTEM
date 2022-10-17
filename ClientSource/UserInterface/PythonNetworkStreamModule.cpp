// Add :

#ifdef ENABLE_TITLE_SYSTEM
PyObject* netSendPlayerSetTitlePacket(PyObject* poSelf, PyObject* poArgs)
{
	int iTitleIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iTitleIndex))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendPlayerSetTitlePacket(static_cast<DWORD>(iTitleIndex));
	return Py_BuildNone();
}
#endif

#ifdef ENABLE_TITLE_SYSTEM
		{ "SendPlayerSetTitlePacket", netSendPlayerSetTitlePacket, METH_VARARGS },
#endif

