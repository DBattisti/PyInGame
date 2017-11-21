// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runnable.h"

/**
 * 
 */
class RUNTIMEPYTHON_API Interpreter : public FRunnable
{
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static  Interpreter* Runnable;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	wchar_t *program;
	FString script;
	FTransform transform;

public:
	Interpreter(FString);
	virtual ~Interpreter();
	void RunText();

	FTransform IsFinished() const {
		return Runnable->transform;
	}

	// Begin FRunnable interface.
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	// End FRunnable interface

	// Makes sure this thread has stopped properly
	void EnsureCompletion();

	/*
	Start the thread and the worker from static (easy access)!
	This code ensures only 1 Prime Number thread will be able to run at a time.
	This function returns a handle to the newly started instance.
	*/
	static Interpreter* ModuleInit(FString);

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

	static FTransform IsThreadFinished();
};
