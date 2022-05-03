// Fill out your copyright notice in the Description page of Project Settings.


#include "SmartObject.h"

#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"

ASmartObject::ASmartObject()
{
	PrimaryActorTick.bCanEverTick = false;

	m_Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	m_Billboard->SetupAttachment(RootComponent);

	m_Direction = CreateDefaultSubobject<UArrowComponent>(TEXT("FacingDirection"));
	m_Direction->SetupAttachment(m_Billboard);

}

void ASmartObject::BeginPlay()
{
	Super::BeginPlay();
	
}