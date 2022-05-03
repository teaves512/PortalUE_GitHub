// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Input_Collision.h"
#include "Components/BoxComponent.h"

APuzzle_Input_Collision::APuzzle_Input_Collision()
{
	m_BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = m_BoxCollision;
	m_BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &APuzzle_Input_Collision::OnBoxBeginOverlap);
	m_BoxCollision->OnComponentEndOverlap.AddDynamic(this, &APuzzle_Input_Collision::OnBoxEndOverlap);

}

void APuzzle_Input_Collision::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (m_bInteractionOn == false)
	{
		SetInteractionOn(true);
		if (m_bActive)
		{
			SetOutputOn(true);
		}
	}
}

void APuzzle_Input_Collision::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (m_bInteractionOn)
	{
		SetInteractionOn(false);
		if (m_bActive)
		{
			SetOutputOn(false);
		}
	}
}
