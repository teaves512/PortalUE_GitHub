// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Hitscan.h"
#include "Components/ArrowComponent.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponHitscan, Display, All);

bool AWeapon_Hitscan::Fire_Implementation()
{
	UE_LOG(LogWeaponHitscan, Display, TEXT("Firing the hitscan weapon class!"));

	UWorld* const world = GetWorld();
	if (world == nullptr) { return false; }

	FHitResult hit(ForceInit);
	UArrowComponent* muzzle = GetGunMuzzle();
	FVector start = ((muzzle != nullptr) ? muzzle->GetComponentLocation() : GetActorLocation());
	FVector end = start + ((muzzle != nullptr) ? muzzle->GetForwardVector() : GetActorForwardVector()) * 1000;

	const FName traceTag("MyTraceTag");
	world->DebugDrawTraceTag = traceTag;
	FCollisionQueryParams collisionParams;
	collisionParams.TraceTag = traceTag;

	if (world->LineTraceSingleByChannel(hit, start, end, ECC_GameTraceChannel2, collisionParams))
	{
		UE_LOG(LogWeaponHitscan, Display, TEXT("Hit position: %s"), *hit.ImpactPoint.ToString());
	}

	return true;
}
