// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalUELevelScriptActor.h"

void APortalUELevelScriptActor::BeginPlay()
{
	for (FStruct_PuzzleLinks link: m_Links)
	{
		for (APuzzle_Component* comp : link.m_PuzzleCompLinks)
		{
			link.m_PuzzleInput->OnLogicalTrigger.AddDynamic(comp, &APuzzle_Component::ReceiveLogicSignal);
		}
	} 
}
