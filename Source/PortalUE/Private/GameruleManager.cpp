// Fill out your copyright notice in the Description page of Project Settings.


#include "GameruleManager.h"

// Sets default values
AGameruleManager::AGameruleManager()
{
	IsMatchEndingRule = false;
}

// Called when the game starts or when spawned
void AGameruleManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGameruleManager::BroadcastGameruleSuccess()
{
	OnGameruleSuccess.Broadcast(this);
}
