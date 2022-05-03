// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameruleManager.h"
#include "Puzzle_Input.h"
#include "Puzzle_Input_Collision.h"
#include "GameruleManager_Course.generated.h"

UCLASS()
class PORTALUE_API AGameruleManager_Course : public AGameruleManager
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OverlapLevelComplete(APuzzle_Input_Collision* delegateInstigator);
	virtual void OverlapLevelComplete_Implementation(APuzzle_Input_Collision* delegateInstigator);
	
};
