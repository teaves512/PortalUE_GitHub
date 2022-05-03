// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LinkMarker.generated.h"

UCLASS()
class PORTALUE_API ALinkMarker : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Particles", meta=(AllowPrivateAccess="true"))
	UParticleSystemComponent* m_LinkParticle;
	
public:
	ALinkMarker();

	void SetParticleActive(bool bActive);
	void SetParticlePosition(FVector Position);

protected:
	virtual void BeginPlay() override;

};
