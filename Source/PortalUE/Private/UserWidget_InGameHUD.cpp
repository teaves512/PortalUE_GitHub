// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget_InGameHUD.h"

void UUserWidget_InGameHUD::SetHPBar(float Percentage)
{
	Percentage = FMath::Clamp(Percentage, 0.0f, 1.0f);
	m_HPBar->SetPercent(Percentage);
}

void UUserWidget_InGameHUD::SetLink1Active(bool bActive)
{
	m_Link1Image->SetVisibility(bActive ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
}

void UUserWidget_InGameHUD::SetLink2Active(bool bActive)
{
	m_Link2Image->SetVisibility(bActive ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
}
