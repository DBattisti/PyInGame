// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Runnable.h"

/**
 * 
 */
class PYINGAME_API PythonInterpreter : public FRunnable
{
	FRunnableThread* Thread;
	FThreadSafeCounter StopTaskCounter;
public:
	PythonInterpreter();
	virtual ~PythonInterpreter() {
	}

	//Implements FRunnable interface
	virtual bool Init() {
	}
	virtual uint32 Run();
	virtual void Stop();
	virtual void Exit();
};
