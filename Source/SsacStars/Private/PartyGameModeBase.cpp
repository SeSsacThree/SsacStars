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

void APartyGameModeBase::AddView()
{
	//PartyUi->AddToViewport();
}

//PartyUi->AddToViewport();

//ui������
//ui���� �ִ� 3���� ��ư�� �ϳ��� �÷��̾ ������ 
//�÷��̾ ������ �ִ� 3���� �ൿ�Լ��� �ϳ��� ȣ��ȴ�
//�׵��ȿ� �������� ������Ѵ�