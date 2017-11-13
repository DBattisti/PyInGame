// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PythonModule
{
public:
	PyObject *pModule, *pGlobal, *pLocal;
	char* nameFunc;
	PythonModule();
	~PythonModule();
};
