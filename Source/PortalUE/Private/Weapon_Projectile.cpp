// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Projectile.h"
#include "Components/ArrowComponent.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponProj, Display, All);

bool AWeapon_Projectile::Fire_Implementation()
{
	UE_LOG(LogWeaponProj, Display, TEXT("Firing projectile weapon class!"));
	UWorld* const world = GetWorld();
	if (world == nullptr || m_Projectile == nullptr) { return false; }

	UArrowComponent* muzzle = GetGunMuzzle();
	FVector spawnLocation = ((muzzle != nullptr) ? muzzle->GetComponentLocation() : GetActorLocation());
	FRotator spawnRotation = ((muzzle != nullptr) ? muzzle->GetComponentRotation() : GetActorRotation());

	FActorSpawnParameters actorSpawnParams;
	actorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	AActor* parentActor = GetParentActor();
	actorSpawnParams.Owner = parentActor;
	actorSpawnParams.Instigator = Cast<APawn>(parentActor);

	world->SpawnActor<AActor>(m_Projectile, spawnLocation, spawnRotation, actorSpawnParams);

	return true;
}
