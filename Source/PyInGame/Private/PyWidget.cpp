// Fill out your copyright notice in the Description page of Project Settings.

#include "PyWidget.h"
#include "Interpreter.h"
#include "GameFramework/Actor.h"


void UPyWidget::ExecuteCode(FString teste) {
	Runnable = Interpreter::RunThisText(teste);
}

void UPyWidget::ApplyResult(AActor* actor) {
	if (Runnable->IsThreadFinished()) {
		actor->SetActorTransform(Runnable->transform);
	}
}