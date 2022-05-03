// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SmartObject.generated.h"

UCLASS()
class PORTALUE_API ASmartObject : public AActor
{
	GENERATED_BODY()
	
public:
	ASmartObject();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	class UBillboardComponent* m_Billboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	class UArrowComponent* m_Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI")
	class UBehaviorTree* m_SubTree;

protected:
	virtual void BeginPlay() override;

};
