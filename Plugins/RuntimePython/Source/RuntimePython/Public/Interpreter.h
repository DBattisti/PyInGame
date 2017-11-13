// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class RUNTIMEPYTHON_API Interpreter
{
	wchar_t *program;
	
public:
	Interpreter(const char*);
	~Interpreter();
	FTransform RunText(FString);
};
