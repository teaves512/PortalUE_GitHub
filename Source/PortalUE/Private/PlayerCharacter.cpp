// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Fireable.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCapsuleSize(42.0f, 96.0f);

	m_BaseTurnRate = 45.0f;
	m_BaseLookUpRate = 45.0f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	m_bSprinting = false;

	marker1 = FVector(0.0f, 0.0f, 0.0f);
	marker2 = FVector(0.0f, 0.0f, 0.0f);

	m_BaseFOV = 90.0f;
	m_MaxFOV = 180.0f;
	m_FOVMultiplier = 0.02f;

	m_FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	m_FirstPersonCamera->SetupAttachment(RootComponent);
	m_FirstPersonCamera->bUsePawnControlRotation = true;

	m_ChildActor_Gun = CreateDefaultSubobject<UChildActorComponent>(TEXT("GunSlot"));
	m_ChildActor_Gun->SetupAttachment(m_FirstPersonCamera);
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	float fov = m_BaseFOV + GetCharacterMovement()->Velocity.Size() * m_FOVMultiplier;
	if (fov > m_MaxFOV) { fov = m_MaxFOV; }

	m_FirstPersonCamera->FieldOfView = fov;
}

void APlayerCharacter::JumpPressed_Implementation()
{
	Jump();
}

void APlayerCharacter::JumpReleased_Implementation()
{
	StopJumping();
}

void APlayerCharacter::SprintPressed_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed * 2;
}

void APlayerCharacter::SprintReleased_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed / 2;
}

void APlayerCharacter::Link1Pressed_Implementation()
{
	marker1 = GetActorLocation();

	AActor* child = m_ChildActor_Gun->GetChildActor();
	if (UKismetSystemLibrary::DoesImplementInterface(child, UFireable::StaticClass()))
	{
		IFireable::Execute_Fire(child);
	}

	m_LinkMarker1Instance->SetParticlePosition(marker1);
	m_LinkMarker1Instance->SetParticleActive(true);
}

void APlayerCharacter::Link1Released_Implementation()
{
	SetActorLocation(marker1);

	m_LinkMarker1Instance->SetParticleActive(false);
}

void APlayerCharacter::Link2Pressed_Implementation()
{
	marker2 = GetActorLocation();

	m_LinkMarker2Instance->SetParticlePosition(marker2);
	m_LinkMarker2Instance->SetParticleActive(true);
}

void APlayerCharacter::Link2Released_Implementation()
{
	SetActorLocation(marker2);

	m_LinkMarker2Instance->SetParticleActive(false);
}

void APlayerCharacter::InteractPressed_Implementation()
{
	UE_LOG(LogTemp, Display, TEXT("Interact."));
}

void APlayerCharacter::InteractReleased_Implementation()
{
}

void APlayerCharacter::MoveForward_Implementation(float _value)
{
	if (Controller != nullptr && _value != 0.0f)
	{
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);

		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, _value);
	}
}

void APlayerCharacter::MoveRight_Implementation(float _value)
{
	if (Controller != nullptr && _value != 0.0f)
	{
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);

		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(direction, _value);
	}
}

void APlayerCharacter::LookUp_Implementation(float _value)
{
	AddControllerPitchInput(_value);
}

void APlayerCharacter::Turn_Implementation(float _value)
{
	AddControllerYawInput(_value);
}

void APlayerCharacter::LookUpRate_Implementation(float _rate)
{
	AddControllerPitchInput(_rate * m_BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::TurnRate_Implementation(float _rate)
{
	AddControllerYawInput(_rate * m_BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::BeginPlay()
{
	//Call the base class
	Super::BeginPlay();

	m_FirstPersonCamera->FieldOfView = m_BaseFOV;

	//create/spawn link markers
	SpawnLinkMarkers();
}

bool APlayerCharacter::SpawnLinkMarkers()
{
	UWorld* const world = GetWorld();
	if (world == nullptr || m_LinkMarker1 == nullptr || m_LinkMarker2 == nullptr) { return false; }
	
	FVector spawnLocation = GetActorLocation();
	FRotator spawnRotation = GetActorRotation();

	FActorSpawnParameters actorSpawnParams;
	actorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	AActor* parentActor = GetParentActor();
	actorSpawnParams.Owner = parentActor;
	actorSpawnParams.Instigator = Cast<APawn>(parentActor);

	m_LinkMarker1Instance = world->SpawnActor<ALinkMarker>(m_LinkMarker1, spawnLocation, spawnRotation, actorSpawnParams);
	m_LinkMarker2Instance = world->SpawnActor<ALinkMarker>(m_LinkMarker2, spawnLocation, spawnRotation, actorSpawnParams);
	
	return true;
}
