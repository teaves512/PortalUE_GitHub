// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolPath.h"

APatrolPath::APatrolPath()
{
	PrimaryActorTick.bCanEverTick = false;

	m_Path = CreateDefaultSubobject<USplineComponent>(TEXT("Path"));
	m_Path->SetupAttachment(RootComponent);
	m_Path->bDrawDebug = true;
}

void APatrolPath::BeginPlay()
{
	Super::BeginPlay();
	GetSplinePoints();
}

void APatrolPath::GetSplinePoints()
{
	for (int i = 0; i <= m_Path->GetNumberOfSplinePoints(); i++)
	{
		m_Locations.Add(m_Path->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World));
	}
}
