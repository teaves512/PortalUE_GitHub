// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Input_EndLevel.h"

#include "Components/BoxComponent.h"
#include "PortalUE/PortalUEGameModeBase.h"

APuzzle_Input_EndLevel::APuzzle_Input_EndLevel()
{
	m_bIsLevelSuccess = false;
}

void APuzzle_Input_EndLevel::BeginPlay()
{
	APortalUEGameModeBase* gameMode = Cast<APortalUEGameModeBase>(GetWorld()->GetAuthGameMode());
	if (gameMode->IsValidLowLevel())
	{
		if (m_bIsLevelSuccess) { OnEndLevelTrigger.AddDynamic(gameMode, &APortalUEGameModeBase::LevelEndReached); }
		else { OnEndLevelTrigger.AddDynamic(gameMode, &APortalUEGameModeBase::LevelFailed); }
	}
}

void APuzzle_Input_EndLevel::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnEndLevelTrigger.Broadcast();
}
