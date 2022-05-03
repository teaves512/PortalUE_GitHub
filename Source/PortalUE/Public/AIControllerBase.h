// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyCharacterBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class PORTALUE_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

	// this class will hold the AI character/pawn
	// create the character/pawn then use this to control it!

public:
	AAIControllerBase(const FObjectInitializer& ObjectInitializer);

	virtual void OnPossess(APawn* InPawn) override;

	AEnemyCharacterBase* m_EnemyCharacter;

	UPROPERTY(transient)
	UBehaviorTreeComponent* m_BehaviourTree;

	UPROPERTY(transient)
	UBlackboardComponent* m_Blackboard;

	uint8 m_EnemyKeyID;
	uint8 m_LocationKeyID;

protected:
	virtual void BeginPlay() override;

};
