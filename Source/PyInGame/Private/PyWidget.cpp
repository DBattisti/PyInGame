// Fill out your copyright notice in the Description page of Project Settings.

#include "PyWidget.h"
#include "Interpreter.h"
#include "GameFramework/Actor.h"


bool UPyWidget::executeCode(AActor* actor, FString teste) {
	Interpreter* Runnable = Interpreter::ModuleInit(teste);
	actor->SetActorTransform(Runnable->IsThreadFinished());
	Runnable->Shutdown();
	return true;
}