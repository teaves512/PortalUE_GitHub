// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle_Input_Collision.h"
#include "Puzzle_Input_EndLevel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndLevelTrigger);

/**
 * 
 */
UCLASS(Abstract)
class PORTALUE_API APuzzle_Input_EndLevel : public APuzzle_Input_Collision
{
	GENERATED_BODY()

public:
	APuzzle_Input_EndLevel();
	
	UPROPERTY(BlueprintAssignable)
	FEndLevelTrigger OnEndLevelTrigger;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="LevelSuccess")
	bool m_bIsLevelSuccess;

private:
	virtual void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
};
