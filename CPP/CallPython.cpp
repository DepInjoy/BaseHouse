#include <iostream>
#include "Python.h"
using namespace std;

int main(int argc, char* argv[])
{
	Py_SetPythonHome("D:/soft/Programs/Python/anaconda3/envs/python27");
	Py_Initialize();

	if (!Py_IsInitialized()){
		cout << "Init python failed !" << endl;
		return -1;
	}


	PyObject* pModule = PyImport_ImportModule("Dict");
	if (!pModule){
		cout << "Get python module failed !";
		return -1;
	}

	PyObject* pv = PyObject_GetAttrString(pModule, "add");
	if (!pv || !PyCallable_Check(pv)){
		cout << "Can't find function !";
		return -1;
	}

	PyObject* arg = Py_BuildValue("(ii)", 2, 6);
	PyObject *pRet = PyObject_CallObject(pv, arg);

	if (PyInt_Check(pRet)){
		int result = PyInt_AsLong(pRet);
		cout << result << endl;
	}
	/*
	int result = -1;
	PyArg_Parse(pRet, "i", &result);
	*/
	Py_Finalize();
	system("pause");
	return 0;
}