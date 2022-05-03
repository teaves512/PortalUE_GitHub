// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Inputable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInputable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PORTALUE_API IInputable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void JumpPressed();
	UFUNCTION(BlueprintNativeEvent)
	void JumpReleased();
	UFUNCTION(BlueprintNativeEvent)
	void SprintPressed();
	UFUNCTION(BlueprintNativeEvent)
	void SprintReleased();
	UFUNCTION(BlueprintNativeEvent)
	void Link1Pressed();
	UFUNCTION(BlueprintNativeEvent)
	void Link1Released();
	UFUNCTION(BlueprintNativeEvent)
	void Link2Pressed();
	UFUNCTION(BlueprintNativeEvent)
	void Link2Released();
	UFUNCTION(BlueprintNativeEvent)
	void InteractPressed();
	UFUNCTION(BlueprintNativeEvent)
	void InteractReleased();

	UFUNCTION(BlueprintNativeEvent)
	void MoveForward(float _value);
	UFUNCTION(BlueprintNativeEvent)
	void MoveRight(float _value);
	UFUNCTION(BlueprintNativeEvent)
	void LookUp(float _value);
	UFUNCTION(BlueprintNativeEvent)
	void Turn(float _value);
	UFUNCTION(BlueprintNativeEvent)
	void LookUpRate(float _rate);
	UFUNCTION(BlueprintNativeEvent)
	void TurnRate(float _rate);
	
};
