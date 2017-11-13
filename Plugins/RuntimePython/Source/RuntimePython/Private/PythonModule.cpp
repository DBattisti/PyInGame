// Fill out your copyright notice in the Description page of Project Settings.

#include "PythonModule.h"
#include "Python.h"

PythonModule::PythonModule()
{
	pGlobal = PyDict_New();
	pModule = PyModule_New("ball");
	PyModule_AddStringConstant(pModule, "__file__", "");
	pLocal = PyModule_GetDict(pModule);
	PyRun_SimpleString(	"posX=0\n"
						"posY=0\n"
						"posZ=0\n"
						"\n");
	nameFunc = "move_object";
}

PythonModule::~PythonModule()
{
}
