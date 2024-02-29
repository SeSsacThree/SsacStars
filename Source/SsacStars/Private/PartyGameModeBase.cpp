// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyPlayer.h"
#include "PartyGameModeBase.h"
//#include "MainUI.h"
#include "Kismet/GameplayStatics.h"


void APartyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//PartyUi = CreateWidget<UMainUI>(GetWorld(), PartyUiFactory);


	TArray<AActor*> PlayerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APartyPlayer::StaticClass(), PlayerActors);

	for (AActor* PlayerActor : PlayerActors)
	{
		APartyPlayer* PartyPlayer = Cast<APartyPlayer>(PlayerActor);
		if (PartyPlayer)
		{
			TurnOrder.Add(PartyPlayer);
		}
	}


		InitialRound();

}


void APartyGameModeBase::CreateWidget()
{
	
}
void APartyGameModeBase::InitialRound()
{
	RoundOrder = TurnOrder;
	
	StartTurn();
}
void APartyGameModeBase::StartTurn()
{
	CurrentPlayer = RoundOrder[0];
	CurrentPlayer->GetCamera();
	//델리게이트로 nextturn실행
}
void APartyGameModeBase::NextTurn()
{
	RoundOrder.RemoveAt(0);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NextTurn"));
	if(RoundOrder.Num() == 0)
	{
		EndRound();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("RoundStart"));
	}
	else
	{
		StartTurn();
	}
}
void APartyGameModeBase::EndRound()
{
	Round++;
	StartMiniGame();
	//미니게임 시작 
}

void APartyGameModeBase::StartMiniGame()
{



	//InitialRound();

}

void APartyGameModeBase::AddView()
{
	//PartyUi->AddToViewport();
}

//PartyUi->AddToViewport();

//ui를띄운다
//ui에서 있는 3가지 버튼중 하나를 플레이어가 누른다 
//플레이어가 가지고 있는 3가지 행동함수중 하나가 호출된다
//그동안엔 움직임이 없어야한다