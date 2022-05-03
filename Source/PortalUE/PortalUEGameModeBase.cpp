// Copyright Epic Games, Inc. All Rights Reserved.


#include "PortalUEGameModeBase.h"

#include "EngineUtils.h"
#include "InGamePlayerController.h"
#include "MatchStateHandler.h"
#include "PlayerCharacter.h"
#include "Puzzle_Input_EndLevel.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Slate/SceneViewport.h"

APortalUEGameModeBase::APortalUEGameModeBase() : Super()
{
	m_CountdownTimer = 3;
}

AActor* APortalUEGameModeBase::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if (m_PlayerStarts.Num() == 0)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), m_PlayerStarts);
	}
	if (m_PlayerStarts.Num() > 0)
	{
		return m_PlayerStarts[0];
	}
	else
	{
		return nullptr;
	}
}

void APortalUEGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	m_PlayerControllers.AddUnique(NewPlayer);
	AInGamePlayerController* castedPC = Cast<AInGamePlayerController>(NewPlayer);
	if (castedPC != nullptr)
	{
		//TODO: bind to any relevant event
		castedPC->Init(this);
	}
	Super::PostLogin(NewPlayer);
}

void APortalUEGameModeBase::Logout(AController* Exiting)
{
	m_PlayerControllers.Remove(Exiting);
	AInGamePlayerController* castedPC = Cast<AInGamePlayerController>(Exiting);
	if (castedPC != nullptr)
	{
		//TODO: unbind from any events
	}
	Super::Logout(Exiting);
}

void APortalUEGameModeBase::PauseGame(AInGamePlayerController* _PC, bool _bPause)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("PausedGame")));
	_PC->SetPause(_bPause);
	if (_bPause)
	{
		_PC->SetInputMode(FInputModeGameAndUI());
		OnShowPauseMenu(true);
	}
	else
	{
		_PC->SetInputMode(FInputModeGameOnly());
		OnShowPauseMenu(false);
	}
}

/*
void APortalUEGameModeBase::ShowPauseMenu_Implementation(bool _bShow)
{
}
*/

void APortalUEGameModeBase::LevelEndReached()
{
	EndMatch();
	OnShowLevelCompleteMenu();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Level Completed!")));
}

void APortalUEGameModeBase::LevelFailed()
{
	EndMatch();
	OnShowLevelFailedMenu();
}

void APortalUEGameModeBase::DecreaseCountdown()
{
	m_CountdownTimer--;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("%d"), m_CountdownTimer));

	if(m_CountdownTimer == 0)
	{
		StartMatch();
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(TimerDecreaseCountdown, this, &APortalUEGameModeBase::DecreaseCountdown, 1.0f, false);
	}
}

void APortalUEGameModeBase::HandleGameruleSuccess(AGameruleManager* delegateInstigator)
{
	if (m_GameruleManagers.Find(delegateInstigator))
	{
		EndMatch();
		OnShowLevelCompleteMenu();
	}
	else
	{
		m_GamerulesLeft--;
		if (m_GamerulesLeft == 0)
		{
			EndMatch();
			OnShowLevelCompleteMenu();
		}
	}
}

void APortalUEGameModeBase::BeginPlay()
{
	UGameplayStatics::RemovePlayer(UGameplayStatics::GetPlayerController(GetWorld(), 0), true);
	
	UGameplayStatics::CreatePlayer(GetWorld());

	m_GamerulesLeft = 0;
	for (TActorIterator<AGameruleManager> It(GetWorld()); It; ++It)
	{
		m_GameruleManagers.Add(*It, It->IsMatchEndingRule);
		
		It->OnGameruleSuccess.AddDynamic(this, &APortalUEGameModeBase::HandleGameruleSuccess);

		if (It->IsMatchEndingRule == false)
		{
			m_GamerulesLeft++;
		}
	}

	AInGamePlayerController* pc = Cast<AInGamePlayerController>(m_PlayerControllers[0]);
	pc->SetInputMode(FInputModeGameOnly());
}

void APortalUEGameModeBase::HandleMatchIsWaitingToStart()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("%d"), m_CountdownTimer));
	GetWorld()->GetTimerManager().SetTimer(TimerDecreaseCountdown, this, &APortalUEGameModeBase::DecreaseCountdown, 1.0f, false);

	Super::HandleMatchIsWaitingToStart();
}

void APortalUEGameModeBase::HandleMatchHasStarted()
{
	if (m_PlayingPawn != nullptr)
	{
		DefaultPawnClass = m_PlayingPawn;
	}

	for (AController* controller : m_PlayerControllers)
	{
		if (UKismetSystemLibrary::DoesImplementInterface(controller, UMatchStateHandler::StaticClass()))
		{
			IMatchStateHandler::Execute_Handle_MatchStarted(controller);
		}
	}
	Super::HandleMatchHasStarted();
}

void APortalUEGameModeBase::HandleMatchHasEnded()
{
	for (AController* controller : m_PlayerControllers)
	{
		if (UKismetSystemLibrary::DoesImplementInterface(controller, UMatchStateHandler::StaticClass()))
		{
			IMatchStateHandler::Execute_Handle_MatchEnded(controller);
		}
	}
	Super::HandleMatchHasEnded();
}

void APortalUEGameModeBase::OnMatchStateSet()
{
	FString output;
	if (MatchState == MatchState::WaitingToStart)
	{
		output = "Waiting To Start";
	}
	else if (MatchState == MatchState::InProgress)
	{
		output = "In Progress";
	}
	else if (MatchState == MatchState::WaitingPostMatch)
	{
		output = "Waiting Post Match";
	}
	else if (MatchState == MatchState::LeavingMap)
	{
		output = "Leaving Map";
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Turquoise, FString::Printf(TEXT("State changed to: %s"), *output));

	Super::OnMatchStateSet();
}

bool APortalUEGameModeBase::ReadyToStartMatch_Implementation()
{
	return false;
}

bool APortalUEGameModeBase::ReadyToEndMatch_Implementation()
{
	return false;
}
