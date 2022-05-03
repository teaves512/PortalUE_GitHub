// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "BouncePad.generated.h"

UCLASS()
class PORTALUE_API ABouncePad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABouncePad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Mesh)
	UStaticMeshComponent* m_Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Trigger)
	UBoxComponent* m_Trigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float m_BounceForce;
};
