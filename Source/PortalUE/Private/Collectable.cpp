// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable.h"
#include "Components/SphereComponent.h"

// Sets default values
ACollectable::ACollectable()
{
	m_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = m_Collider;
}

// Called when the game starts or when spawned
void ACollectable::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACollectable::BroadcastOnCollected()
{
	OnCollected.Broadcast(this);
	Destroy();
}
