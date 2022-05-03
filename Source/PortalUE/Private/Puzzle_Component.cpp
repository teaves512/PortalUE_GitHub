// Fill out your copyright notice in the Description page of Project Settings.

#include "Puzzle_Component.h"

APuzzle_Component::APuzzle_Component()
{
	m_bStartActive = false;
	m_bActive = false;
}

void APuzzle_Component::ReceiveLogicSignal(APuzzle_Input* signalSender, bool on)
{
	if (m_bActive != on)
	{
		SetActive(on);
	}
}

void APuzzle_Component::SetActive_Implementation(bool active)
{
	m_bActive = active;
}

void APuzzle_Component::BeginPlay()
{
	if (m_bActive != m_bStartActive)
	{
		SetActive(m_bStartActive);
	}
	
	Super::BeginPlay();
}
