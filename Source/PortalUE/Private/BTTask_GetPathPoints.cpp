// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetPathPoints.h"

#include "AIController.h"
#include "EnemyCharacterBase.h"
#include "PatrolPath.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UBTTask_GetPathPoints::UBTTask_GetPathPoints(const FObjectInitializer& ObjectInitializer)
{
	bCreateNodeInstance = true;
	NodeName = "Get Path Points";
}

EBTNodeResult::Type UBTTask_GetPathPoints::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	
	AAIController* controller = OwnerComp.GetAIOwner();
	AEnemyCharacterBase* enemy = Cast<AEnemyCharacterBase>(controller->GetPawn());
	
	if (!controller || !blackboard || !enemy)
	{
		return EBTNodeResult::Failed;
	}

	APatrolPath* pathRef = Cast<APatrolPath>(enemy->m_SmartObject);
	if (!pathRef || pathRef->m_Locations.Num() == 0)
	{
		return EBTNodeResult::Succeeded;
	}

	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>("MoveToLocation", pathRef->m_Locations[m_Index]);

	if (m_Index < pathRef->m_Locations.Num() - 1)
	{
		m_Index++;
		return EBTNodeResult::Succeeded;
	}
	else
	{
		m_Index = 0;
		return EBTNodeResult::Succeeded;
	}
}
