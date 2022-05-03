// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MatchStateHandler.h"
#include "UserWidget_InGameHUD.h"
#include "GameFramework/PlayerController.h"
#include "PortalUE/PortalUEGameModeBase.h"
#include "InGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PORTALUE_API AInGamePlayerController : public APlayerController, public IMatchStateHandler
{
	GENERATED_BODY()

public:
	AInGamePlayerController();
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init(APortalUEGameModeBase* _gameMode);
	virtual void Init_Implementation(APortalUEGameModeBase* _gameMode);

	virtual void Handle_MatchStarted_Implementation() override;
	virtual void Handle_MatchEnded_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	UUserWidget_InGameHUD* m_HUD;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> PawnToSpawn;

	APortalUEGameModeBase* m_GameMode;

	UFUNCTION(BlueprintImplementableEvent, Category="HUD")
	void ShowHUD();

private:
	void PausePressed(); void PauseReleased();
	void JumpPressed(); void JumpReleased();
	void SprintPressed(); void SprintReleased();
	void InteractPressed(); void InteractReleased();
	void Link1Pressed(); void Link1Released();
	void Link2Pressed(); void Link2Released();

	void MoveForward(float _value);
	void MoveRight(float _value);
	void LookUp(float _value);
	void Turn(float _value);
	void LookUpRate(float _rate);
	void TurnRate(float _rate);
};
