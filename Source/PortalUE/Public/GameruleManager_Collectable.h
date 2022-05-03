// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectable.h"
#include "GameruleManager.h"
#include "GameruleManager_Collectable.generated.h"

/**
 * 
 */
UCLASS()
class PORTALUE_API AGameruleManager_Collectable : public AGameruleManager
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ACollectable*> m_Collectables;

	int m_AmountRemaining;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Collected(ACollectable* delegateInstigator);
	virtual void Collected_Implementation(ACollectable* delegateInstigator);
	
};
