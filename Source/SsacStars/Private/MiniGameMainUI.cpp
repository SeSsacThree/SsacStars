// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGameMainUI.h"
#include "TimerManager.h"
#include "KartPlayer.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


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

void UMiniGameMainUI::GetReadyCount()
{
	num--;
	FText ReadyCountText = FText::FromString(FString::FromInt(num));
	ReadyCount->SetText(ReadyCountText);
	if(num==0)
	{
		const char* text = "S t a r t !";
		ReadyCountText = FText::FromString(ANSI_TO_TCHAR(text));
		ReadyCount->SetText(ReadyCountText);
		
	}
	if(num<0)
	{
		HideReady();
		auto player = Cast<AKartPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AKartPlayer::StaticClass()));
		player->isPaused = false;
	}
}

void UMiniGameMainUI::HideReady()
{
	ReadyCount->SetVisibility(ESlateVisibility::Hidden);
}

void UMiniGameMainUI::CountDown()
{
	auto player = Cast<AKartPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AKartPlayer::StaticClass()));
	if(false==player->isPaused)
	{
		if (sec != 0)
		{
			--sec;
		}
		else
		{
			if (min == 0)
			{
				// game over
			}
			else
			{
				--min;
				sec = 59;
			}
		}
		FText minText = FText::FromString(FString::FromInt(min));
		Minutes->SetText(minText);
		FText secText = FText::FromString(FString::FromInt(sec));
		Seconds->SetText(secText);
	}
	

}

