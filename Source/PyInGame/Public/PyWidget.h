// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interpreter.h"
#include "PyWidget.generated.h"

/**
 * 
 */
UCLASS()
class PYINGAME_API UPyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	Interpreter* Runnable;
	
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void ExecuteCode(FString teste);
	
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void ApplyResult(AActor* actor);
};
