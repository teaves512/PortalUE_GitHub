// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puzzle_Component.generated.h"

class APuzzle_Input;

UCLASS(Abstract)
class PORTALUE_API APuzzle_Component : public AActor
{
	GENERATED_BODY()
	
public:
	APuzzle_Component();

	UFUNCTION(BlueprintCallable)
	virtual void ReceiveLogicSignal(APuzzle_Input* signalSender, bool on);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool m_bStartActive;
	bool m_bActive;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetActive(bool _active);
	virtual void SetActive_Implementation(bool active);
	
	virtual void BeginPlay() override;

};
