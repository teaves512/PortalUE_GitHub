// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmartObject.h"
#include "Components/SplineComponent.h"
#include "PatrolPath.generated.h"

/**
 * 
 */
UCLASS()
class PORTALUE_API APatrolPath : public ASmartObject
{
	GENERATED_BODY()

public:
	APatrolPath();
	
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="SplinePath")
	USplineComponent* m_Path;

	void GetSplinePoints();

	TArray<FVector> m_Locations;
	
};
