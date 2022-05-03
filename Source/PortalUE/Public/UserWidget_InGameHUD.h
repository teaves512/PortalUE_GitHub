// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "UserWidget_InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class PORTALUE_API UUserWidget_InGameHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHPBar(float Percentage);

	void SetLink1Active(bool bActive);
	void SetLink2Active(bool bActive);

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UProgressBar* m_HPBar;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* m_Link1Image;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* m_Link2Image;
	
};

// TODO: Rather than spawning the HUD in blueprints, spawn it from the PlayerController class so that you can get a reference to it and then change the health bar.