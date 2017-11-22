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
	bool bTermined;
	bool bNewScript;
	void RunText();

public:
	FTransform transform;

	Interpreter(FString);
	virtual ~Interpreter();

	bool IsFinished() const {
		UE_LOG(LogTemp, Warning, TEXT(":::::IsFinished:::::\n"));
		return this->transform.IsValid();
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
	This function returns a handle to the newly started instance.
	*/
	static Interpreter* RunThisText(FString);

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

	static bool IsThreadFinished();
};
