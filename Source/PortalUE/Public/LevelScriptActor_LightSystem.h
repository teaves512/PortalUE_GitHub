// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PortalUELevelScriptActor.h"
#include "Puzzle_Input.h"
#include "Engine/LevelScriptActor.h"
#include "LevelScriptActor_LightSystem.generated.h"

class APuzzle_Component;
class APuzzle_Input;

UCLASS()
class PORTALUE_API ALevelScriptActor_LightSystem : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FStruct_PuzzleLinks> m_Links;

	virtual void BeginPlay() override;
};
