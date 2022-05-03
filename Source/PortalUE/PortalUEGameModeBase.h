// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameruleManager.h"
#include "Puzzle_Input_EndLevel.h"
#include "GameFramework/GameMode.h"
#include "PortalUEGameModeBase.generated.h"

class AInGamePlayerController;

/**
 * 
 */
UCLASS()
class PORTALUE_API APortalUEGameModeBase : public AGameMode
{
	GENERATED_BODY()
	
public:
	APortalUEGameModeBase();

	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	void PauseGame(AInGamePlayerController* _PC, bool _bPause);

	UFUNCTION()
	void LevelEndReached();

	UFUNCTION()
	void LevelFailed();
	
protected:
	TArray<AActor*> m_PlayerStarts;

	UFUNCTION(BlueprintImplementableEvent, Category="Pause")
	void OnShowPauseMenu(bool _bShow);
	
	UFUNCTION(BlueprintImplementableEvent, Category="WinLoss")
	void OnShowLevelCompleteMenu();

	UFUNCTION(BlueprintImplementableEvent, Category="WinLoss")
	void OnShowLevelFailedMenu();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AController*> m_PlayerControllers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MatchManagement")
	int m_CountdownTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MatchManagement")
	TSubclassOf<APawn> m_PlayingPawn;

	int m_GamerulesLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MatchManagement")
	TMap<AGameruleManager*, bool> m_GameruleManagers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LevelEnd")
	APuzzle_Input_EndLevel* m_LevelEnd;

	FTimerHandle TimerDecreaseCountdown;
	UFUNCTION()
	void DecreaseCountdown();

	UFUNCTION()
	void HandleGameruleSuccess(AGameruleManager* delegateInstigator);

	virtual void BeginPlay() override;

	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;

	virtual void OnMatchStateSet() override;

	virtual bool ReadyToStartMatch_Implementation() override;
	virtual bool ReadyToEndMatch_Implementation() override;
	
};
