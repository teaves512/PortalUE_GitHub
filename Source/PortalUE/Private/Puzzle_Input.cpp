// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Input.h"

APuzzle_Input::APuzzle_Input()
{
	m_bStartActive = true;
	m_bActive = true;
	m_bStartOn = false;
	m_bOutputOn = false;
	m_bInteractionOn = false;
}

APuzzle_Input::~APuzzle_Input()
{
	OnLogicalTrigger.Clear();
}

void APuzzle_Input::BeginPlay()
{
	Super::BeginPlay();

	if (m_bStartOn)
	{
		SetOutputOn(true);
	}
}

void APuzzle_Input::SetOutputOn_Implementation(bool on)
{
	m_bOutputOn = on;
	BroadcastLogicalTrigger(on);
}

void APuzzle_Input::SetInteractionOn_Implementation(bool on)
{
	m_bInteractionOn = on;
}

void APuzzle_Input::ReceiveLogicSignal(APuzzle_Input* signalSender, bool on)
{
	if (m_bActive != on)
	{
		SetActive(on);
		if (m_bInteractionOn)
		{
			SetOutputOn(on);
		}
	}
}

void APuzzle_Input::BroadcastLogicalTrigger(bool on)
{
	OnLogicalTrigger.Broadcast(this, on);
}