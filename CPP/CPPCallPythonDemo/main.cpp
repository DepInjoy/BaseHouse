#include <iostream>
#include "Python.h"
using namespace std;

int main(int argc, char* argv[])
{
	Py_Initialize(); 	
	if (!Py_IsInitialized()){
		cout << "Init python failed !" << endl;
		return -1;
	}

	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");

	PyObject* pModule = PyImport_ImportModule("Dict");
	if (!pModule){
		cout << "Get python module failed !";
		return -1;
	}

	PyObject* pv = PyObject_GetAttrString(pModule, "showList");
	if (!pv || !PyCallable_Check(pv)){
		cout << "Can't find function !";
		return -1;
	}

	int length = 10;
	PyObject* pyList = PyList_New(length);
	for (int i = 0; i<length; i++)
	{
		PyList_SetItem(pyList, i, PyFloat_FromDouble(i));
	}

	PyObject* arg = PyTuple_New(1);
	PyTuple_SetItem(arg, 0, pyList);
	PyObject *pRet = PyObject_CallObject(pv, arg);
	Py_Finalize();
	system("pause");
	return 0;
}