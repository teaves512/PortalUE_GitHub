// Fill out your copyright notice in the Description page of Project Settings.

#include "GameruleManager_Collectable.h"
#include "EngineUtils.h"

void AGameruleManager_Collectable::BeginPlay()
{
	if (m_Collectables.Num() == 0)
	{
		for(TActorIterator<ACollectable> It(GetWorld()); It; ++It)
		{
			m_Collectables.Add(*It);
		}
	}

	for (ACollectable* col : m_Collectables)
	{
		col->OnCollected.AddDynamic(this, &AGameruleManager_Collectable::Collected);
	}

	m_AmountRemaining = m_Collectables.Num();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, FString::Printf(TEXT("Collectables remaining: %d"), m_AmountRemaining));
	Super::BeginPlay();
}

void AGameruleManager_Collectable::Collected_Implementation(ACollectable* delegateInstigator)
{
	m_AmountRemaining--;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, FString::Printf(TEXT("Collectables remaining: %d"), m_AmountRemaining));
	if (m_AmountRemaining == 0)
	{
		BroadcastGameruleSuccess();
	}
}
