// Fill out your copyright notice in the Description page of Project Settings.


#include "LinkMarker.h"

#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

ALinkMarker::ALinkMarker()
{
	m_LinkParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LinkParticle"));
	m_LinkParticle->SetupAttachment(RootComponent);
}

void ALinkMarker::SetParticleActive(bool bActive)
{
	m_LinkParticle->SetActive(bActive);
}

void ALinkMarker::SetParticlePosition(FVector Position)
{
	SetActorLocation(Position);
}

void ALinkMarker::BeginPlay()
{
	SetParticleActive(false);	
}
