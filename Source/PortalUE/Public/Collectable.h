// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCollectedSignature, class ACollectable*, delegateInstigator);

class USphereComponent;

UCLASS(Abstract)
class PORTALUE_API ACollectable : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	USphereComponent* m_Collider;
	
public:	
	// Sets default values for this actor's properties
	ACollectable();

	UPROPERTY(BlueprintAssignable)
	FCollectedSignature OnCollected;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void BroadcastOnCollected();

};
