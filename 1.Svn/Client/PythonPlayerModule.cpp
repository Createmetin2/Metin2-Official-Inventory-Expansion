//Find
PyObject * playerGetElk(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonPlayer::Instance().GetStatus(POINT_GOLD));
}

///Add
#ifdef ENABLE_EXTEND_INVEN_SYSTEM
PyObject * playerGetEnvanter(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonPlayer::Instance().GetStatus(POINT_BLACK));
}

//Find
		{ "GetMoney",					playerGetElk,						METH_VARARGS },

///Add
#ifdef ENABLE_EXTEND_INVEN_SYSTEM
		{ "GetEnvanter",				playerGetEnvanter,						METH_VARARGS },
#endif