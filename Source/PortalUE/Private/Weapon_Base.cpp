// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Base.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponBase, Display, All);

AWeapon_Base::AWeapon_Base()
{
	m_Root = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
	RootComponent = m_Root;

	m_GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	m_GunMesh->SetupAttachment(m_Root);

	m_GunMuzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("GunMuzzle"));
	m_GunMuzzle->SetupAttachment(m_GunMesh);
}

bool AWeapon_Base::Fire_Implementation()
{
	UE_LOG(LogWeaponBase, Display, TEXT("Firing the weapon base class!"));
	return true;
}

void AWeapon_Base::BeginPlay()
{
	Super::BeginPlay();
	
}
