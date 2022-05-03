// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle_Input.h"
#include "Puzzle_Input_Collision.generated.h"

class UBoxComponent;

/**
 * 
 */
UCLASS(Abstract)
class PORTALUE_API APuzzle_Input_Collision : public APuzzle_Input
{
	GENERATED_BODY()

public:
	APuzzle_Input_Collision();

protected:
	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* m_BoxCollision;

	UFUNCTION()
	virtual void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
