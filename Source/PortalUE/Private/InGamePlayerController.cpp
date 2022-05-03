// Fill out your copyright notice in the Description page of Project Settings.


#include "InGamePlayerController.h"
#include "Inputable.h"
#include "PlayerCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


AInGamePlayerController::AInGamePlayerController() : Super()
{
}

void AInGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	SetShowMouseCursor(false);
	
	FInputActionBinding& pauseAction = InputComponent->BindAction("Pause", IE_Pressed, this, &AInGamePlayerController::PausePressed);
	pauseAction.bExecuteWhenPaused = true;
	InputComponent->BindAction("Pause", IE_Released, this, &AInGamePlayerController::PauseReleased);
	
	InputComponent->BindAction("Jump", IE_Pressed, this, &AInGamePlayerController::JumpPressed);
	InputComponent->BindAction("Jump", IE_Released, this, &AInGamePlayerController::JumpReleased);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AInGamePlayerController::SprintPressed);
	InputComponent->BindAction("Sprint", IE_Released, this, &AInGamePlayerController::SprintReleased);
	InputComponent->BindAction("Link1", IE_Pressed, this, &AInGamePlayerController::Link1Pressed);
	InputComponent->BindAction("Link1", IE_Released, this, &AInGamePlayerController::Link1Released);
	InputComponent->BindAction("Link2", IE_Pressed, this, &AInGamePlayerController::Link2Pressed);
	InputComponent->BindAction("Link2", IE_Released, this, &AInGamePlayerController::Link2Released);

	InputComponent->BindAxis("MoveForward", this, &AInGamePlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AInGamePlayerController::MoveRight);
	InputComponent->BindAxis("LookUp", this, &AInGamePlayerController::LookUp);
	InputComponent->BindAxis("Turn", this, &AInGamePlayerController::Turn);
	InputComponent->BindAxis("LookUpRate", this, &AInGamePlayerController::LookUpRate);
	InputComponent->BindAxis("TurnRate", this, &AInGamePlayerController::TurnRate);

}

void AInGamePlayerController::Init_Implementation(APortalUEGameModeBase* _gameMode)
{
	m_GameMode = _gameMode;
	if (GetPawn() != nullptr)
	{
		GetPawn()->Destroy();
	}
}

void AInGamePlayerController::Handle_MatchStarted_Implementation()
{
	if (GetPawn() != nullptr)
	{
		GetPawn()->Destroy();
	}

	UWorld* const world = GetWorld();

	AActor* tempStart = UGameplayStatics::GetGameMode(world)->FindPlayerStart(this);
	FVector spawnLocation = ((tempStart != nullptr) ? tempStart->GetActorLocation() : FVector::ZeroVector);
	FRotator spawnRotation = ((tempStart != nullptr) ? tempStart->GetActorRotation() : FRotator::ZeroRotator);

	FActorSpawnParameters actorSpawnParams;
	actorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	APawn* tempPawn = world->SpawnActor<APawn>(UGameplayStatics::GetGameMode(world)->DefaultPawnClass, spawnLocation, spawnRotation, actorSpawnParams);
	
	Possess(tempPawn);
	ShowHUD();
}

void AInGamePlayerController::Handle_MatchEnded_Implementation()
{
	//SetInputMode(FInputModeUIOnly());
}

void AInGamePlayerController::PausePressed()
{
	m_GameMode->PauseGame(this, !IsPaused());
}

void AInGamePlayerController::PauseReleased()
{
}

void AInGamePlayerController::JumpPressed()
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_JumpPressed(pawn);
	}
}

void AInGamePlayerController::JumpReleased()
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_JumpReleased(pawn);
	}
}

void AInGamePlayerController::SprintPressed()
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_SprintPressed(pawn);
	}
}

void AInGamePlayerController::SprintReleased()
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_SprintReleased(pawn);
	}
}

void AInGamePlayerController::InteractPressed()
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_InteractPressed(pawn);
	}
}

void AInGamePlayerController::InteractReleased()
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_InteractReleased(pawn);
	}
}

void AInGamePlayerController::Link1Pressed()
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_Link1Pressed(pawn);
	}
	if (m_HUD != nullptr) { m_HUD->SetLink1Active(true); }
}

void AInGamePlayerController::Link1Released()
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_Link1Released(pawn);
	}
	if (m_HUD != nullptr) { m_HUD->SetLink1Active(false); }
}

void AInGamePlayerController::Link2Pressed()
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_Link2Pressed(pawn);
	}
	if (m_HUD != nullptr) { m_HUD->SetLink2Active(true); }
}

void AInGamePlayerController::Link2Released()
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_Link2Released(pawn);
	}
	if (m_HUD != nullptr) { m_HUD->SetLink2Active(false); }
}

void AInGamePlayerController::MoveForward(float _value)
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_MoveForward(pawn, _value);
	}
}

void AInGamePlayerController::MoveRight(float _value)
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_MoveRight(pawn, _value);
	}
}

void AInGamePlayerController::LookUp(float _value)
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_LookUp(pawn, _value);
	}
}

void AInGamePlayerController::Turn(float _value)
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_Turn(pawn, _value);
	}
}

void AInGamePlayerController::LookUpRate(float _rate)
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_LookUpRate(pawn, _rate);
	}
}

void AInGamePlayerController::TurnRate(float _rate)
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_TurnRate(pawn, _rate);
	}
}
