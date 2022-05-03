// Fill out your copyright notice in the Description page of Project Settings.


#include "BouncePad.h"

// Sets default values
ABouncePad::ABouncePad()
{
	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	m_BounceForce = 10000.0f;
}

void ABouncePad::BeginPlay()
{
	Super::BeginPlay();
}
