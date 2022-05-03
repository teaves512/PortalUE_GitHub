// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_Base.h"
#include "Weapon_Projectile.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PORTALUE_API AWeapon_Projectile : public AWeapon_Base
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Projectile")
	TSubclassOf<AActor> m_Projectile; //change this from an AActor to a projectile class

public:
	virtual bool Fire_Implementation() override;
	
};
