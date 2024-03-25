// Fill out your copyright notice in the Description page of Project Settings.


#include "CountDownWidget.h"

#include "KartPlayer.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"


void UCountDownWidget::CountDown( int32 inMin , int32 inSec )
{
	min = inMin;
	sec = inSec;
	
	FText minText = FText::FromString( FString::FromInt( min ) );
	Minutes->SetText( minText );
	FText secText = FText::FromString( FString::FromInt( sec ) );
	Seconds->SetText( secText );

}

void UCountDownWidget::GetReadyCount(int32 inNum)
{
	
	FText ReadyCountText = FText::FromString( FString::FromInt( inNum ) );
	ReadyCount->SetText( ReadyCountText );

	if (inNum == 0)
	{
		const char* text = "S t a r t !";
		ReadyCountText = FText::FromString( ANSI_TO_TCHAR( text ) );
		ReadyCount->SetText( ReadyCountText );

	}
	if (inNum < 0)
	{
		HideReady();
		auto player = Cast<AKartPlayer>( UGameplayStatics::GetActorOfClass( GetWorld() , AKartPlayer::StaticClass() ) );
		player->isPaused = false;
		
	}
}

void UCountDownWidget::HideReady()
{
	ReadyCount->SetVisibility( ESlateVisibility::Hidden );
}



