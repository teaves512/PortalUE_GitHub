// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerBase.h"

#include "EnemyCharacterBase.h"
#include "SmartObject.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AAIControllerBase::AAIControllerBase(const FObjectInitializer& ObjectInitializer)
{
	m_BehaviourTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourTree"));
	m_Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
}

void AAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AEnemyCharacterBase* enemy = Cast<AEnemyCharacterBase>(InPawn);
	if (enemy != nullptr && enemy->m_BehaviourTree != nullptr)
	{
		m_Blackboard->InitializeBlackboard(*enemy->m_BehaviourTree->BlackboardAsset);

		m_EnemyKeyID = m_Blackboard->GetKeyID("TargetActor");
		m_EnemyKeyID = m_Blackboard->GetKeyID("MoveToLocation");

		m_BehaviourTree->StartTree(*enemy->m_BehaviourTree);
	}
}

void AAIControllerBase::BeginPlay()
{
	if (!m_EnemyCharacter)
	{
		AEnemyCharacterBase* enemy = Cast<AEnemyCharacterBase>(GetPawn());
		if (!enemy) { return; }
		m_EnemyCharacter = enemy;
	}
	if (m_EnemyCharacter->m_SmartObject)
	{
		FGameplayTag SubTag;
		m_BehaviourTree->SetDynamicSubtree(SubTag, m_EnemyCharacter->m_SmartObject->m_SubTree);
	}
}
