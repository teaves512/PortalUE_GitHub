// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle_Component.h"
#include "Puzzle_Input.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLogicalTriggerSignature, class APuzzle_Input*, signalSender, bool, on);

UCLASS(Abstract)
class PORTALUE_API APuzzle_Input : public APuzzle_Component
{
	GENERATED_BODY()

public:
	APuzzle_Input();
	~APuzzle_Input();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable)
	FLogicalTriggerSignature OnLogicalTrigger;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool m_bStartOn;
	UPROPERTY(BlueprintReadOnly)
	bool m_bOutputOn;
	UPROPERTY(BlueprintReadOnly)
	bool m_bInteractionOn;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetOutputOn(bool on);
	virtual void SetOutputOn_Implementation(bool on);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetInteractionOn(bool on);
	virtual void SetInteractionOn_Implementation(bool on);

	virtual void ReceiveLogicSignal(APuzzle_Input* signalSender, bool on) override;

	void BroadcastLogicalTrigger(bool on);

};
