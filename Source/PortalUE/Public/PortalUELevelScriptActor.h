// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle_Component.h"
#include "Puzzle_Input.h"
#include "Engine/LevelScriptActor.h"
#include "PortalUELevelScriptActor.generated.h"

class APuzzle_Component;
class APuzzle_Input;

USTRUCT(BlueprintType)
struct FStruct_PuzzleLinks
{
	GENERATED_BODY()
	FStruct_PuzzleLinks()
	{
		m_PuzzleInput = nullptr;
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	APuzzle_Input* m_PuzzleInput;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APuzzle_Component*> m_PuzzleCompLinks;
};

UCLASS()
class PORTALUE_API APortalUELevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FStruct_PuzzleLinks> m_Links;

	virtual void BeginPlay() override;
};
