// Fill out your copyright notice in the Description page of Project Settings.


#include "KartGameState.h"

#include "CountDownWidget.h"
#include "ItemWidget.h"
#include "KartPlayer.h"
#include "MiniGameMainUI.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"


void AKartGameState::BeginPlay()
{
	Super::BeginPlay();

	countDownUI = CreateWidget<UCountDownWidget>( GetWorld() , CountDownUIFactory );
	countDownUI->AddToViewport();

	FTimerHandle Handle1;
	GetWorldTimerManager().SetTimer( Handle1 , this , &AKartGameState::ReadyTimer , 1.0f , true , 3.0 );

	FTimerHandle Handle2;
	GetWorld()->GetTimerManager().SetTimer( Handle2 , FTimerDelegate::CreateLambda(
		[this]()->void
		{
			FTimerHandle Handle3;
			GetWorld()->GetTimerManager().SetTimer( Handle3 , FTimerDelegate::CreateLambda(
				[this]()->void
				{
					CountDown();
				}
			) , DelayTime , true );
			
		}
	) , 5 , false );
}

void AKartGameState::CountDown()
{
	if (sec != 0)
	{
		--sec;
	}
	else
	{
		if (min == 0)
		{
			auto player = Cast<AKartPlayer>( UGameplayStatics::GetActorOfClass( GetWorld() , AKartPlayer::StaticClass() ) );
			player->isPaused = true;
			player->isEnd = true;
			player->MainUI->RemoveFromParent();
			player->itemUI->RemoveFromParent();
		}
		else
		{
			--min;
			sec = 59;
		}
	}
	countDownUI->CountDown(min,sec);
}

void AKartGameState::ReadyTimer()
{
	num--;
	countDownUI->GetReadyCount(num);
}

void AKartGameState::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( AKartGameState , min );
	DOREPLIFETIME( AKartGameState , sec );
	DOREPLIFETIME( AKartGameState , num );
}
