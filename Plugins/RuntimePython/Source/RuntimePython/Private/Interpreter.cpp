// Fill out your copyright notice in the Description page of Project Settings.

#include "Interpreter.h"
#include "Python.h"
#include "RunnableThread.h"
#include "PlatformProcess.h"
#include "PythonModule.h"

Interpreter* Interpreter::Runnable = NULL;

Interpreter::Interpreter(FString source)
{
	this->script = source;
	Thread = FRunnableThread::Create(this, TEXT("Interpreter"), 0, TPri_BelowNormal); //windows default = 8mb for thread, could specify more
}

Interpreter::~Interpreter()
{
	if (Py_FinalizeEx() < 0) {
		exit(120);
	}
	PyMem_RawFree(this->program);

	delete Thread;
	Thread = NULL;
}

bool Interpreter::Init()
{
	program = Py_DecodeLocale("teste", NULL);
	Py_SetProgramName(this->program);
	Py_Initialize();

	return true;
}

uint32 Interpreter::Run()
{
	//Initial wait before starting
	FPlatformProcess::Sleep(0.03);
	if (StopTaskCounter.GetValue() == 0) {
		Runnable->RunText();
	}
	return 0;
}

Interpreter* Interpreter::ModuleInit(FString source) 
{
	//Create new instance of thread if it does not exist
	//		and the platform supports multi threading!
	if (!Runnable && FPlatformProcess::SupportsMultithreading())
	{
		Runnable = new Interpreter(source);
	}
	return Runnable;
}

void Interpreter::Stop()
{
	StopTaskCounter.Increment();
}

void Interpreter::EnsureCompletion()
{
	Stop();
	Thread->WaitForCompletion();
}

void Interpreter::Shutdown()
{
	if (Runnable)
	{
		Runnable->EnsureCompletion();
		delete Runnable;
		Runnable = NULL;
	}
}

FTransform Interpreter::IsThreadFinished()
{
	if (Runnable) return Runnable->IsFinished();
	return FTransform();
}

void Interpreter::RunText()
{
	PyObject *pPosx, *pPosy, *pPosz, *pValue;

	Py_Initialize();

	//Criando um novo modulo
	PythonModule pyModule;

	UE_LOG(LogTemp, Warning, TEXT("The source code passed is:\n%s\n"), *this->script);

	//Define my function in the newly created module	def blah(x):\n\ty = x * 5\n\treturn y\n
	pValue = PyRun_String(TCHAR_TO_UTF8(*this->script), Py_file_input, pyModule.pGlobal, pyModule.pLocal);

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
	this->transform.SetLocation(FVector(PyLong_AsLong(pPosx), PyLong_AsLong(pPosy), PyLong_AsLong(pPosz)));

	UE_LOG(LogTemp, Warning, TEXT("Returned value: %ld\n"), PyLong_AsLong(pPosx));

	Py_DECREF(pValue);
}