// Fill out your copyright notice in the Description page of Project Settings.


#include "GameruleManager_Course.h"

#include "GameFramework/GameModeBase.h"
#include "PortalUE/PortalUEGameModeBase.h"

void AGameruleManager_Course::BeginPlay()
{
	Super::BeginPlay();
}

void AGameruleManager_Course::OverlapLevelComplete_Implementation(APuzzle_Input_Collision* delegateInstigator)
{
	//Cast<APortalUEGameModeBase>(GetWorld()->GetLevelScriptActor());
	BroadcastGameruleSuccess();
}
