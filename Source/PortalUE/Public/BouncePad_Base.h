// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Exertable.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "BouncePad_Base.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UArrowComponent;

UCLASS(Abstract)
class PORTALUE_API ABouncePad_Base : public AActor, public IExertable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABouncePad_Base();

	virtual bool ExertForce_Implementation(AActor* OtherActor) override;

	FORCEINLINE UArrowComponent* GetPadDirection() const { return m_PadDirection; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BouncePad")
	float m_BounceForce;

private:
	UPROPERTY(VisibleDefaultsOnly)
	UArrowComponent* m_PadDirection;

	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* m_BoxCollision;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
