// Fill out your copyright notice in the Description page of Project Settings.
#include "PartyGameModeBase.h"
#include "PartyPlayer.h"
#include "MainUI.h"
#include "ItemUI.h"
#include "TrapWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "EngineUtils.h"
#include "PartyScore.h"

void APartyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//SelectUi = CreateWidget<UMainUI>(GetWorld(), SelectUiFactory);
	SelectUi = NewObject<UMainUI>(this, SelectUiFactory);
	StatusUi = NewObject<UUserWidget>(this, StatusUiFactory);
	ItemUi = NewObject<UItemUI>(this, ItemUiFactory);
	TrapUi= NewObject<UTrapWidget>(this, TrapUiFactory);
	TArray<AActor*> PlayerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APartyPlayer::StaticClass(), PlayerActors);
	Star = Cast<APartyScore>(UGameplayStatics::GetActorOfClass(GetWorld(), APartyScore::StaticClass()));

	for (AActor* PlayerActor : PlayerActors)
	{
		APartyPlayer* PartyPlayer = Cast<APartyPlayer>(PlayerActor);
		if (PartyPlayer)
		{
			TurnOrder.Add(PartyPlayer);

		}
	}
	StatusUi->AddToViewport();
	
	InitialRound();
}


void APartyGameModeBase::AddItemUseUi()
{
	ItemUi->AddToViewport();
	

}
void APartyGameModeBase::InitialRound()
{
	RoundOrder = TurnOrder;

	StartTurn();
}
void APartyGameModeBase::StartTurn()
{
	if (RoundOrder.IsEmpty()) {
		return;
	}

	CurrentPlayer = RoundOrder[0];

	CurrentPlayer->GetCamera();
	//ChangeStarSpace();

	//��������Ʈ�� nextturn����
}
void APartyGameModeBase::NextTurn()
{
	RoundOrder.RemoveAt(0);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NextTurn"));
	if (RoundOrder.Num() == 0)
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



	InitialRound();

}

void APartyGameModeBase::AddSelectBehaviorUi()
{
	SelectUi->AddToViewport();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("addviewport"));


	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
	}
}



void APartyGameModeBase::CloseView()
{
	ItemUi->RemoveFromParent();
	SelectUi->RemoveFromParent();
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false;
		PlayerController->bEnableClickEvents = false;
		PlayerController->bEnableMouseOverEvents = false;
	}

}

void APartyGameModeBase::ChangeStarSpace()
{
	//���� ���ӽ����Ҷ� ȣ��������� 
	//�ʻ��� ��� �����߿��� �ϳ��� ���

	// UClass�� ���� ���͸��� Ŭ������ ����


	TArray<ABlueBoardSpace*> FoundSpaces;
	for (TActorIterator<ABlueBoardSpace> It(GetWorld()); It; ++It)
	{
		ABlueBoardSpace* Space = *It;

		// "Star" �Ǵ� "Warp" ���°� �ƴ� ������ ã��
		if (Space->SpaceState != ESpaceState::Star && Space->SpaceState != ESpaceState::Warp)
		{
			FoundSpaces.Add(Space);
		}
		
	}
	if (FoundSpaces.Num() > 0)
	{
		// �����ϰ� ���� ����
		ABlueBoardSpace* SelectedSpace = FoundSpaces[FMath::RandRange(0, FoundSpaces.Num() - 1)];

		// ���� ���¸� ���� ���·� ����
		CurrentPlayer->CurrentSpace->SpaceState = CurrentPlayer->CurrentSpace->PreviousState;

		// ���õ� ������ �������¸� �ֽ�ȭ
		SelectedSpace->PreviousState = SelectedSpace->SpaceState;
		// ���õ� ������ "Star" ���·� ����

		SelectedSpace->SpaceState = ESpaceState::Star;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("StarSwitch"));
		SelectedSpace->UpdateAppearance();
	}
	// �׹����� star,warp ������ �ƴ϶��
	// ���� �ڽ��� state�� previousstate�� �����ϰ�
	// star state ���·� �ٲ۴�
	

	Star->ReSpace();


}

void APartyGameModeBase::AddTrapUi()
{
	TrapUi->AddToViewport();
	
}



