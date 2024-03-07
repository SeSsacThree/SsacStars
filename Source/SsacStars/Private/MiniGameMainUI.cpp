// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGameMainUI.h"
#include "TimerManager.h"
#include "KartPlayer.h"
#include "Components/TextBlock.h"

void UMiniGameMainUI::SetStarCount()
{
	auto player = Cast<AKartPlayer>(GetOwningPlayerPawn());
	if(player)
	{
		FText StarCountText = FText::FromString(FString::FromInt(player->starCount));
		if (StarCount)
		{
			StarCount->SetText(StarCountText);
		}
	}
}

