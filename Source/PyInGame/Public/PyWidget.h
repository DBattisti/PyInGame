// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Python.h"

#include "PyWidget.generated.h"

class PyHelper
{
public:
	char* stdOutErr;
	PyObject *pModule;

	PyHelper()
	{
		stdOutErr = "import sys\n"
					"class CatchOutErr:\n"
					"	def __init__(self):\n"
					"		self.value = ''\n"
					"	def write(self, txt):\n"
					"		self.value += txt\n"
					"catchOutErr = CatchOutErr()\n"
					"sys.stdout = catchOutErr\n"
					"sys.stderr = catchOutErr\n";

		Py_Initialize();
		pModule = PyImport_AddModule("__main__");
		PyRun_SimpleString(stdOutErr);
	}

	~PyHelper()
	{
		Py_Finalize();
	}
};

UCLASS()
class PYINGAME_API UPyWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "PyWidget")
	FString ExecuteItPyScript(FString Script) {
		PyHelper Ph;
		char *result = "";
		
		PyRun_SimpleString(TCHAR_TO_UTF8(*Script)); 
		PyObject *catcher = PyObject_GetAttrString(Ph.pModule, "catchOutErr");
		PyErr_Print(); 

		PyObject *output = PyObject_GetAttrString(catcher, "value"); 
		Py_DECREF(catcher);

		if (PyUnicode_Check(output)) {
			PyObject* temp_bytes = PyUnicode_AsEncodedString(output, "ASCII", "strict"); 
			if (temp_bytes != NULL) {
				result = PyBytes_AS_STRING(temp_bytes);
				Py_DECREF(temp_bytes);
			}
		}
		Py_DECREF(output);
		
		return FString(result);
	};
	
};
