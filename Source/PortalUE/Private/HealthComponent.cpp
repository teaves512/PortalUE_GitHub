// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "Kismet/GameplayStatics.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	m_MaxHP = 100.0f;
	m_bRegenHP = true;
	m_HPRegenRate = 10.0f;
	m_HPRegenDelay = 2.0f;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	m_CurrentHP = m_MaxHP;
}

void UHealthComponent::DamageTaken(AActor* damagedActor, float damage, const UDamageType* damageType,
	AController* instigator, AActor* causer)
{
	m_HPRegenDelayTimer = m_HPRegenDelay;
	m_CurrentHP = FMath::Max(m_CurrentHP - damage, 0.0f);

	if (m_CurrentHP <= 0.0f) { onComponentDead.Broadcast(instigator); }
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_CurrentHP == m_MaxHP || !m_bRegenHP) { return; }
	
	if (m_HPRegenDelayTimer > 0.0f)
	{
		m_HPRegenDelayTimer -= DeltaTime;
	}
	else
	{
		m_CurrentHP = FMath::Min(m_MaxHP, m_CurrentHP + (m_HPRegenRate * DeltaTime));
	}
}
