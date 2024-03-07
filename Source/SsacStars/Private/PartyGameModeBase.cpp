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

	//델리게이트로 nextturn실행
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
	//미니게임 시작 
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
	//따라서 게임시작할때 호출해줘야함 
	//맵상의 모든 발판중에서 하나를 골라

	// UClass를 통해 필터링할 클래스를 지정


	TArray<ABlueBoardSpace*> FoundSpaces;
	for (TActorIterator<ABlueBoardSpace> It(GetWorld()); It; ++It)
	{
		ABlueBoardSpace* Space = *It;

		// "Star" 또는 "Warp" 상태가 아닌 발판을 찾음
		if (Space->SpaceState != ESpaceState::Star && Space->SpaceState != ESpaceState::Warp)
		{
			FoundSpaces.Add(Space);
		}
		
	}
	if (FoundSpaces.Num() > 0)
	{
		// 랜덤하게 발판 선택
		ABlueBoardSpace* SelectedSpace = FoundSpaces[FMath::RandRange(0, FoundSpaces.Num() - 1)];

		// 현재 상태를 이전 상태로 저장
		CurrentPlayer->CurrentSpace->SpaceState = CurrentPlayer->CurrentSpace->PreviousState;

		// 선택된 발판의 이전상태를 최신화
		SelectedSpace->PreviousState = SelectedSpace->SpaceState;
		// 선택된 발판을 "Star" 상태로 변경

		SelectedSpace->SpaceState = ESpaceState::Star;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("StarSwitch"));
		SelectedSpace->UpdateAppearance();
	}
	// 그발판이 star,warp 발판이 아니라면
	// 현재 자신의 state를 previousstate에 저장하고
	// star state 상태로 바꾼다
	

	Star->ReSpace();


}

void APartyGameModeBase::AddTrapUi()
{
	TrapUi->AddToViewport();
	
}



