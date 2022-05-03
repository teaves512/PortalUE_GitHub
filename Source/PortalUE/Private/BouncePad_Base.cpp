// Fill out your copyright notice in the Description page of Project Settings.


#include "BouncePad_Base.h"
#include "BouncePad.h"
#include "PlayerCharacter.h"

#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBouncePadBase, Display, All);

// Sets default values
ABouncePad_Base::ABouncePad_Base()
{
	PrimaryActorTick.bCanEverTick = false;

	m_BounceForce = 1000.0f;

	m_BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PadTrigger"));
	RootComponent = m_BoxCollision;

	m_PadDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("PadDirection"));
	m_PadDirection->SetupAttachment(m_BoxCollision);
}

bool ABouncePad_Base::ExertForce_Implementation(AActor* OtherActor)
{
	APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);
	player->GetCharacterMovement()->Launch(m_PadDirection->GetForwardVector() * m_BounceForce);
	
	return true;
}

void ABouncePad_Base::BeginPlay()
{
	Super::BeginPlay();

	m_BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABouncePad_Base::OnBoxBeginOverlap);
}

void ABouncePad_Base::OnBoxBeginOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ExertForce_Implementation(OtherActor);
}
