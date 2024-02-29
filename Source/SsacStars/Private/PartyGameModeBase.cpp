// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetArrayLibrary.h"

void APartyGameModeBase::BeginPlay()
{
	Super::BeginPlay();


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
	//��������Ʈ�� nextturn����
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
	//�̴ϰ��� ���� 
}

void APartyGameModeBase::StartMiniGame()
{



	//InitialRound();

}
