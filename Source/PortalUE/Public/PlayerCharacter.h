// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inputable.h"
#include "LinkMarker.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UChildActorComponent;

UCLASS()
class PORTALUE_API APlayerCharacter : public ACharacter, public IInputable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	UChildActorComponent* m_ChildActor_Gun;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta = (AllowPrivateAccess="true"))
	class UCameraComponent* m_FirstPersonCamera;

	UPROPERTY(EditAnywhere, Category="Marker")
	TSubclassOf<ALinkMarker> m_LinkMarker1;
	ALinkMarker* m_LinkMarker1Instance;

	UPROPERTY(EditAnywhere, Category="Marker")
	TSubclassOf<ALinkMarker> m_LinkMarker2;
	ALinkMarker* m_LinkMarker2Instance;

	UPROPERTY(EditAnywhere, Category="Camera")
	float m_BaseFOV;
	UPROPERTY(EditAnywhere, Category="Camera")
	float m_MaxFOV;
	UPROPERTY(EditAnywhere, Category="Camera")
	float m_FOVMultiplier;

	UPROPERTY()
	bool m_bSprinting;

	FVector marker1;
	FVector marker2;

public:
	APlayerCharacter();

	virtual void Tick(float DeltaSeconds) override;

#pragma region IInputable_interface

	virtual void JumpPressed_Implementation() override;
	virtual void JumpReleased_Implementation() override;
	virtual void SprintPressed_Implementation() override;
	virtual void SprintReleased_Implementation() override;
	virtual void Link1Pressed_Implementation() override;
	virtual void Link1Released_Implementation() override;
	virtual void Link2Pressed_Implementation() override;
	virtual void Link2Released_Implementation() override;
	virtual void InteractPressed_Implementation() override;
	virtual void InteractReleased_Implementation() override;

	virtual void MoveForward_Implementation(float _value) override;
	virtual void MoveRight_Implementation(float _value) override;
	virtual void LookUp_Implementation(float _value) override;
	virtual void Turn_Implementation(float _value) override;
	virtual void LookUpRate_Implementation(float _rate) override;
	virtual void TurnRate_Implementation(float _rate) override;
	
#pragma endregion
	
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float m_BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float m_BaseLookUpRate;

protected:
	virtual void BeginPlay() override;

	bool SpawnLinkMarkers();
};
