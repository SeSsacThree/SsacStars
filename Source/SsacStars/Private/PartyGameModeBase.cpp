// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyGameModeBase.h"
#include "PartyPlayer.h"

#include "RollDiceCharacter.h"

#include "Kismet/GameplayStatics.h"

#include "PartyController.h"
#include "PartyGameStateBase.h"
#include "PartyScore.h"


APartyGameModeBase::APartyGameModeBase()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh1(TEXT("C:/Users/MSI/Desktop/SsacStars (1)/Content/CJW/Models/ZZang/Shinchan_Models.uasset"));
	if (tempMesh1.Succeeded())
	{
		Mesh1 = tempMesh1.Object;
	}
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh2(TEXT("C:/Users/MSI/Desktop/SsacStars (1)/Content/KMS/MiniGame/Mesh/pingu/pingu.uasset"));
	if (tempMesh2.Succeeded())
	{
		Mesh2 = tempMesh2.Object;
	}
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh3(TEXT("C:/Users/MSI/Desktop/SsacStars (1)/Content/JYS/Kirby/source/kirby.uasset"));
	if (tempMesh3.Succeeded())
	{
		Mesh3 = tempMesh3.Object;
	}
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh4(TEXT("/Script/Engine.StaticMesh'/Game/CJW/Models/ZZang/KERORO.KERORO'"));
	if (tempMesh1.Succeeded())
	{
		Mesh4 = tempMesh4.Object;
	}
	PlayerControllerClass = APartyController::StaticClass();
}

void APartyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//SelectUi = CreateWidget<UMainUI>(GetWorld(), SelectUiFactory);

	PlayerSetting();


	//StatusUi->AddToViewport();

	InitialRound();
}


void APartyGameModeBase::PlayerSetting()
{

	PartyGameState = GetGameState<APartyGameStateBase>();

	PartyGameState->CurrentPlayerIndex = 0;
	//CurrentPlayer = 0;
	TArray<AActor*> PlayerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APartyPlayer::StaticClass(), PlayerActors);
	RollDiceCharacter = Cast<ARollDiceCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ARollDiceCharacter::StaticClass()));
	Star = Cast<APartyScore>(UGameplayStatics::GetActorOfClass(GetWorld(), APartyScore::StaticClass()));
	for (AActor* PlayerActor : PlayerActors)
	{
		APartyPlayer* PartyPlayer = Cast<APartyPlayer>(PlayerActor);
		if (PartyPlayer)
		{
			TurnOrder.Add(PartyPlayer);

		}
	}
	//StatusUi->AddToViewport();
	//PartyGameState->ServerViewStatusUi();

	InitialTurnOrder = TurnOrder;
	PartyGameState->PlayerList = InitialTurnOrder;
	for (int i = 0; i < InitialTurnOrder.Num(); i++)
	{
		//맨처음에 이니션 턴오더 에 각 player index가 플레이어 에게도 생김 0,1,2,3 지정
		InitialTurnOrder[i]->PlayerIndex = i;
		//서버 요청 필요 
		//SetPlayerAppeareance(InitialTurnOrder[i], i);
		PartyGameState->ServerUpdateAppeareance(InitialTurnOrder[i], i);
	}
	/*
	StatusUi->PersonalState->SetProfile(0);
	StatusUi->PersonalState1->SetProfile(1);
	StatusUi->PersonalState2->SetProfile(2);
	StatusUi->PersonalState3->SetProfile(3);
	*/
	PlayerCoins.SetNum(InitialTurnOrder.Num());
	PlayerCoins.Init(0, InitialTurnOrder.Num());
	PlayerScores.SetNum(InitialTurnOrder.Num());
	PlayerScores.Init(0, InitialTurnOrder.Num());

}

void APartyGameModeBase::SetPlayerAppeareance(APartyPlayer* Player, int Index)
{
	switch (Index)
	{
	case 0:
	{
		Player->GetMesh()->SetSkeletalMeshAsset(Mesh1);
		Player->GetMesh()->SetWorldScale3D(FVector(16));
		break;
	}
	case 1:
	{
		Player->GetMesh()->SetSkeletalMeshAsset(Mesh2);
		Player->GetMesh()->SetWorldScale3D(FVector(0.4));
		break;
	}
	case 2:
	{
		Player->GetMesh()->SetSkeletalMeshAsset(Mesh3);
		Player->GetMesh()->SetWorldScale3D(FVector(17));
		break;
	}
	case 3:
	{
		Player->GetMesh()->SetSkeletalMeshAsset(Mesh4);
		Player->GetMesh()->SetWorldScale3D(FVector(1));
		break;
	}
	}
}

void APartyGameModeBase::SetRollerAppeareance(ARollDiceCharacter* Player, int Index)
{
	switch (Index)
	{
	case 0:
	{
		Player->MeshComp->SetSkeletalMeshAsset(Mesh1);
		Player->MeshComp->SetWorldScale3D(FVector(16));
		break;
	}
	case 1:
	{
		Player->MeshComp->SetSkeletalMeshAsset(Mesh2);
		Player->MeshComp->SetWorldScale3D(FVector(0.4));
		break;
	}
	case 2:
	{
		Player->MeshComp->SetSkeletalMeshAsset(Mesh3);
		Player->MeshComp->SetWorldScale3D(FVector(17));
		break;
	}
	case 3:
	{
		Player->MeshComp->SetSkeletalMeshAsset(Mesh4);
		Player->MeshComp->SetWorldScale3D(FVector(1));
		break;
	}

	}
}
void APartyGameModeBase::AddItemUseUi()
{
	//ItemUi->AddToViewport();
//	PartyGameState->ServerViewItemUi();

}
void APartyGameModeBase::InitialRound()
{

	StartTurn();
}
void APartyGameModeBase::StartTurn()
{
	if (InitialTurnOrder.IsEmpty()) {
		return;
	}
	CurrentPlayerIndex = PartyGameState->CurrentPlayerIndex;

	CurrentPlayer = InitialTurnOrder[CurrentPlayerIndex];
	PartyGameState->CurrentPlayer = CurrentPlayer;
	//서버요청필요
	PartyGameState->ServerMoveCameraToPlayer(CurrentPlayer);

	CurrentPlayer->GetCamera();
	//ChangeStarSpace();

	//델리게이트로 nextturn실행
}
void APartyGameModeBase::NextTurn()
{

	//CurrentPlayerIndex를 한명이 주사위를 던질때마 추가한다
	PartyGameState->CurrentPlayerIndex++;
	//CurrentPlayerIndex++;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NextTurn"));

	//현재 플레이 하고 있는 플레이어의 수랑  인덱스의 수가 같아지면 라운드종료 
	if (PartyGameState->CurrentPlayerIndex == InitialTurnOrder.Num())
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
	PartyGameState->CurrentPlayerIndex = 0;
	//CurrentPlayerIndex = 0;
	if (Round > 2)
	{
		StartMiniGame();
	}
	else
	{
		//다시 맨처음 플레이어 부터 주사위 사이클 시작
		InitialRound();
	}

	//미니게임 시작 
}

void APartyGameModeBase::StartMiniGame()
{
	/*
		//open
		FName LevelName = TEXT("D:/GitHub/SsacStars/Content/KMS/Maps/MiniGame_Kart.umap");
		UGameplayStatics::LoadStreamLevel(GetWorld(), LevelName, true, true, FLatentActionInfo());
		//UGameplayStatics::OpenLevel(GetWorld(),TEXT("MiniGame_Kart"));
		*/
}

void APartyGameModeBase::AddSelectBehaviorUi()
{
	PartyGameState->ServerViewSelectUi();
	//SelectUi->AddToViewport();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("addviewport"));

	//현재 플레이어 턴의 인덱스에 해당하는 플레이어만 가질수 있게 접근이 필요
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;

	}
}



void APartyGameModeBase::CloseView()
{
	/*
	PartyGameState->ServerRemoveItemUi();
	PartyGameState->ServerRemoveSelectUi();
	//ItemUi->RemoveFromParent();
	//SelectUi->RemoveFromParent();
	//현재 플레이어의 턴의 인덱스에 해당하는 플레이어만 사라지게 접근이 필요
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false;
		PlayerController->bEnableClickEvents = false;

	}
	*/
}

void APartyGameModeBase::ChangeStarSpace()
{
	//따라서 게임시작할때 호출해줘야함 
	//맵상의 모든 발판중에서 하나를 골라

	// UClass를 통해 필터링할 클래스를 지정

	/*
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
	*/
	PartyGameState->ServerChangeStarSpace();
}
/*
void APartyGameModeBase::AddTrapUi()
{
	TrapUi->AddToViewport();
	삭제 및 변환필요
}
*/
/*
void APartyGameModeBase::AddGetItemUi()
{
	GetItemUi->AddToViewport();
}
*/
/*
void APartyGameModeBase::AddTenCoinsforaStar()
{
	TenCoinsforaStarUi->AddToViewport();
}
*/
void APartyGameModeBase::UpdateGameInfo(int Index)
{
	/*
	switch (Index)
	{
		case 0:
			{
			StatusUi->PersonalState[0].SetStarScoreText(CurrentPlayer->Score);
			StatusUi->PersonalState[0].SetSpaceTypeBorder(CurrentPlayer);
			break;
			}
		case 1:
		{
			StatusUi->PersonalState[1].SetStarScoreText(CurrentPlayer->Score);
			StatusUi->PersonalState[1].SetSpaceTypeBorder(CurrentPlayer);
			break;
		}
		case 2:
		{
			StatusUi->PersonalState[2].SetStarScoreText(CurrentPlayer->Score);
			StatusUi->PersonalState[2].SetSpaceTypeBorder(CurrentPlayer);
			break;
		}
		case 3:
		{
			StatusUi->PersonalState[3].SetStarScoreText(CurrentPlayer->Score);
			StatusUi->PersonalState[3].SetSpaceTypeBorder(CurrentPlayer);
			break;
		}

	}
	*/
}

void APartyGameModeBase::UpdateRankInfo()
{
	/*
		//현재 플레이어의 인덱스를 넣으면 ex 1
		StatusUi->PersonalState->SetTurnOrderScoreText(CurrentPlayer->PlayerIndex);
		StatusUi->PersonalState1->SetTurnOrderScoreText(CurrentPlayer->PlayerIndex);
		StatusUi->PersonalState2->SetTurnOrderScoreText(CurrentPlayer->PlayerIndex);
	//	StatusUi->PersonalState3->SetTurnOrderScoreText(CurrentPlayer->PlayerIndex);

		//플레이어 목록이 담겨있는 각 스코어에 접근하여 플레이어 스코에저장
		for(int i=0;i<InitialTurnOrder.Num();i++ )
		{
			if(InitialTurnOrder[i]->Score)
				PlayerScores[i] = InitialTurnOrder[i]->Score;

		}
	//순위 정렬을 위해 TempArray를 만들고
		TArray<int> TempArray;
		TempArray.SetNum(InitialTurnOrder.Num());
	//Initial 의 크기 만큼 Temp크기를 설정하고
		int Count;

		for(int i=0;i< InitialTurnOrder.Num();i++)
		{
			Count = 0;
			for(int t=0;t< InitialTurnOrder.Num();t++)
			{
				if(PlayerScores[i]<PlayerScores[t])
				{
					Count++;
				}
			}
			TempArray[i] = Count + 1;
		}
		//3번째 playerscore 인덱스의 등수는  temparry3






		for (int t = 0; t < InitialTurnOrder.Num(); t++)
		{
			StatusUi->PersonalState->SetMainScoreText(InitialTurnOrder[t]->Rank);

		}

		*/
}

void APartyGameModeBase::GamePause()
{



	if (PlayerController)
	{
		// 게임을 일시정지합니다.
		PlayerController->SetPause(true);
	}
}

void APartyGameModeBase::GameRelease()
{
	if (PlayerController)
	{
		// 게임을 일시정지합니다.
		PlayerController->SetPause(false);
	}
}



