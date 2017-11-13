// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PyWidget.generated.h"

/**
 * 
 */
UCLASS()
class PYINGAME_API UPyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Widget")
	FTransform executeCode(FString teste);

	
	
	
};
