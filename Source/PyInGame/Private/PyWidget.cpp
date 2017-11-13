// Fill out your copyright notice in the Description page of Project Settings.

#include "PyWidget.h"
#include "Interpreter.h"

FTransform UPyWidget::executeCode(FString teste) {
	Interpreter inter("teste");
	FTransform modData =  inter.RunText(teste);
	return modData;
}