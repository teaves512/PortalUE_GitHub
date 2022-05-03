// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InGamePlayerController.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FComponentDeadSignature, AController*, causer);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALUE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category="Components")
	FComponentDeadSignature onComponentDead;
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Health")
	float m_CurrentHP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Health")
	float m_MaxHP;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Health")
	bool m_bRegenHP;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Health")
	float m_HPRegenDelayTimer;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Health")
	float m_HPRegenRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Health")
	float m_HPRegenDelay;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void DamageTaken(AActor* damagedActor, float damage, const UDamageType* damageType, AController* instigator, AActor* causer);
	
};
