// Fill out your copyright notice in the Description page of Project Settings.

#include "Interpreter.h"
#include "Python.h"
#include "PythonModule.h"

Interpreter::Interpreter(const char* programName)
{
	program = Py_DecodeLocale(programName, NULL);
	Py_SetProgramName(program);
	Py_Initialize();
}

Interpreter::~Interpreter()
{
	if (Py_FinalizeEx() < 0) {
		exit(120);
	}
	PyMem_RawFree(program);
}

FTransform Interpreter::RunText(FString sCode)
{
	PyObject *pPosx, *pPosy, *pPosz, *pValue;

	Py_Initialize();

	//Criando um novo modulo
	PythonModule pyModule;
	FTransform transform;

	UE_LOG(LogTemp, Warning, TEXT("The source code passed is:\n%s\n"), *sCode);

	//Define my function in the newly created module	def blah(x):\n\ty = x * 5\n\treturn y\n
	pValue = PyRun_String(TCHAR_TO_UTF8(*sCode), Py_file_input, pyModule.pGlobal, pyModule.pLocal);

	//pValue would be null if the Python syntax is wrong, for example
	if (pValue == NULL) {
		if (PyErr_Occurred()) {
			UE_LOG(LogTemp, Warning, TEXT("Error Occurred in code execution\n"));
		}
	}

	Py_DECREF(pValue);

	pPosx = PyObject_GetAttrString(pyModule.pModule, "posX");
	pPosy = PyObject_GetAttrString(pyModule.pModule, "posY");
	pPosz = PyObject_GetAttrString(pyModule.pModule, "posZ");
	transform.SetLocation(FVector(PyLong_AsLong(pPosx), PyLong_AsLong(pPosy), PyLong_AsLong(pPosz)));

	UE_LOG(LogTemp, Warning, TEXT("Returned value: %ld\n"), PyLong_AsLong(pPosx));

	Py_DECREF(pValue);

	return transform;
}