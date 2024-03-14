// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyGameStateBase.h"
#include "MainUI.h"
#include "StatusUi.h"
#include "ItemUI.h"
#include "TenCoinsforaStar.h"
#include "PlayerUiCard.h"
#include "Components/Image.h"
#include "TrapWidget.h"
#include "RandomItemWidget.h"
#include "PartyPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "EngineUtils.h"
#include "GetCoins.h"
#include "GetCoins_Pingu.h"
#include "Components/WrapBox.h"


void APartyGameStateBase::BeginPlay()
{
	Super::BeginPlay();
	SelectUi = NewObject<UMainUI>(this, SelectUiFactory);
	StatusUi = NewObject<UStatusUi>(this, StatusUiFactory);
	ItemUi = NewObject<UItemUI>(this, ItemUiFactory);
	GetCoinsUi = NewObject<UGetCoins>(this, GetCoinsUiFactory);
	UGetCoins_PinguUi = NewObject<UGetCoins_Pingu>(this, UGetCoins_PinguUiFactory);
	TrapUi = NewObject<UTrapWidget>(this, TrapUiFactory);
	ItemUi = NewObject<UItemUI>(this, ItemUiFactory);
	TrapUi = NewObject<UTrapWidget>(this, TrapUiFactory);
	GetItemUi = NewObject<URandomItemWidget>(this, GetItemUiFactory);
	TenCoinsforaStarUi = NewObject<UTenCoinsforaStar>(this, TenCoinsforaStarUiFactory);

	GM = Cast<APartyGameModeBase>(GetWorld()->GetAuthGameMode());
	Star = Cast<APartyScore>(UGameplayStatics::GetActorOfClass(GetWorld(), APartyScore::StaticClass()));





}

void APartyGameStateBase::ServerMoveCameraToStar_Implementation()
{
	MultiMoveCameraToPlayer(CurrentPlayer);
}

void APartyGameStateBase::MultiMoveCameraToStar_Implementation()
{
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	OurPlayerController->SetViewTargetWithBlend(Star, 1.0f);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("StarChange"));
	DelayTime(1.0f, [this]()
		{

			ServerMoveCameraToPlayer(CurrentPlayer);
		});

}

void APartyGameStateBase::ServerUpdateAppeareance_Implementation(APartyPlayer* Player, int Index)
{
	MultiUpdateAppeareance(Player, Index);
}

void APartyGameStateBase::MultiUpdateAppeareance_Implementation(APartyPlayer* Player, int Index)
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





void APartyGameStateBase::ServerMoveCameraToPlayer_Implementation(APartyPlayer* InPlayer)
{

	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), APartyGameCamera::StaticClass(), PlayerCamera);

	/*for (APawn* PlayerActor : PlayerCamera)
	{
		APartyGameCamera* PartyPlayer = Cast<APartyGameCamera>(PlayerActor);
		if (PartyPlayer)
		{
			CameraList.Add(PartyPlayer);
			PlayerCount++;
		}
	}*/

	MultiMoveCameraToPlayer(InPlayer);
}
void APartyGameStateBase::MultiMoveCameraToPlayer_Implementation(APartyPlayer* InPlayer)
{
	/*
	// 존재하는 모든 플레이어 컨트롤러를 가져와서
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PlayerController = Iterator->Get();
		//컨트롤러를 찾으면 그 플레이어가 client를 외치도록한다
		if (PlayerController)
		{
			// 각 플레이어의 카메라를 GM->CurrentPlayer의 위치로 이동
			ClientMoveCameraToPlayer();

		}
	}

	*/
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	OurPlayerController->SetViewTargetWithBlend(InPlayer, 1.0f);
	/*
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PlayerController = It->Get();
		if (PlayerController)
		{
			APawn* MyPawn = PlayerController->GetPawn();

			// 폰이 APartyGameCamera 클래스의 인스턴스인지 확인
			APartyGameCamera* MyCamera = Cast<APartyGameCamera>(MyPawn);
			if (MyCamera)
			{
				// 여기에서 플레이어 컨트롤러에 대해 원하는 작업 수행
				MyCamera->MoveCameraLocation();
			}
		}
	}
*/
}
void APartyGameStateBase::ServerViewStatusUi_Implementation()
{

	MultiViewStatusUi();
}

void APartyGameStateBase::MultiViewStatusUi_Implementation()
{
	StatusUi->AddToViewport();
}

void APartyGameStateBase::ServerViewItemUi_Implementation()
{
	MultiViewItemUi();
}

void APartyGameStateBase::MultiViewItemUi_Implementation()
{
	ItemUi->AddToViewport();
}

void APartyGameStateBase::ServerViewSelectUi_Implementation()
{
	MultiViewSelectUi();
}

void APartyGameStateBase::MultiViewSelectUi_Implementation()
{
	SelectUi->AddToViewport();
}
void APartyGameStateBase::ServerViewTrapUi_Implementation()
{
	MultiViewTrapUi();
}

void APartyGameStateBase::MultiViewTrapUi_Implementation()
{
	TrapUi->AddToViewport();
}

void APartyGameStateBase::ServerViewTenCoinsforaStarUi_Implementation()
{
	MultiViewTenCoinsforaStarUi();
}

void APartyGameStateBase::MultiViewTenCoinsforaStarUi_Implementation()
{
	TenCoinsforaStarUi->AddToViewport();
}
void APartyGameStateBase::ServerGetCoinsUi_Implementation()
{
	MultiGetCoinsUi();
}

void APartyGameStateBase::MultiGetCoinsUi_Implementation()
{
	GetCoinsUi->AddToViewport();
}

void APartyGameStateBase::ServerGetCoins_PinguUi_Implementation()
{
	MultiGetCoins_PinguUi();
}

void APartyGameStateBase::MultiGetCoins_PinguUi_Implementation()
{
	UGetCoins_PinguUi->AddToViewport();
}
void APartyGameStateBase::ServerRemoveSelectUi_Implementation()
{
	MultiRemoveSelectUi();
}

void APartyGameStateBase::MultiRemoveSelectUi_Implementation()
{
	SelectUi->RemoveFromParent();
}

void APartyGameStateBase::ServerRemoveItemUi_Implementation()
{
	MultiRemoveItemUi();
}

void APartyGameStateBase::MultiRemoveItemUi_Implementation()
{
	ItemUi->RemoveFromParent();
}

void APartyGameStateBase::ServerChangeStarSpace_Implementation()
{

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
		ABlueBoardSpace* SelectedSpace = FoundSpaces[FMath::RandRange(0, FoundSpaces.Num() - 1)];
		MultiChangeStarSpace(SelectedSpace);
	}



}

void APartyGameStateBase::MultiChangeStarSpace_Implementation(ABlueBoardSpace* Space)
{
	//맵상 모든 발판을 검사해서 FOundSpace안에 넣고

	//검사하여 확인된 발판이 있다면 
	if (FoundSpaces.Num() > 0)
	{
		// 랜덤하게 발판 선택
		ABlueBoardSpace* Space = FoundSpaces[FMath::RandRange(0, FoundSpaces.Num() - 1)];

		// 현재 상태를 이전 상태로 저장
		CurrentPlayer->CurrentSpace->SpaceState = CurrentPlayer->CurrentSpace->PreviousState;

		// 선택된 발판의 이전상태를 최신화
		Space->PreviousState = Space->SpaceState;
		// 선택된 발판을 "Star" 상태로 변경

		Space->SpaceState = ESpaceState::Star;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("StarSwitch"));
		Space->UpdateAppearance();
	}
	// 그발판이 star,warp 발판이 아니라면
	// 현재 자신의 state를 previousstate에 저장하고
	// star state 상태로 바꾼다


	Star->ReSpace();
	ServerMoveCameraToStar();


}


void APartyGameStateBase::ServerUpdateGameInfo_Implementation(int Index)
{
	MultiUpdateGameInfo(Index);
}

void APartyGameStateBase::MultiUpdateGameInfo_Implementation(int Index)
{
	/*
	switch (Index)
	{
	case 0:
	{
		StatusUi->PersonalState[0].SetStarScoreText(GM->CurrentPlayer->Score);
		StatusUi->PersonalState[0].SetSpaceTypeBorder(GM->CurrentPlayer);
		break;
	}
	case 1:
	{
		StatusUi->PersonalState[1].SetStarScoreText(GM->CurrentPlayer->Score);
		StatusUi->PersonalState[1].SetSpaceTypeBorder(GM->CurrentPlayer);
		break;
	}
	case 2:
	{
		StatusUi->PersonalState[2].SetStarScoreText(GM->CurrentPlayer->Score);
		StatusUi->PersonalState[2].SetSpaceTypeBorder(GM->CurrentPlayer);
		break;
	}
	case 3:
	{
		StatusUi->PersonalState[3].SetStarScoreText(GM->CurrentPlayer->Score);
		StatusUi->PersonalState[3].SetSpaceTypeBorder(GM->CurrentPlayer);
		break;
	}

	}
	*/

}

void APartyGameStateBase::ServerUpdateRankInfo_Implementation()
{
	MultiUpdateRankInfo();
}

void APartyGameStateBase::MultiUpdateRankInfo_Implementation()
{
	//현재 플레이어의 인덱스를 넣으면 ex 1
	/*
	StatusUi->PersonalState->SetTurnOrderScoreText(GM->CurrentPlayer->PlayerIndex);
	StatusUi->PersonalState1->SetTurnOrderScoreText(GM->CurrentPlayer->PlayerIndex);
	StatusUi->PersonalState2->SetTurnOrderScoreText(GM->CurrentPlayer->PlayerIndex);
	//	StatusUi->PersonalState3->SetTurnOrderScoreText(CurrentPlayer->PlayerIndex);

		//플레이어 목록이 담겨있는 각 스코어에 접근하여 플레이어 스코에저장
	for (int i = 0; i < GM->InitialTurnOrder.Num(); i++)
	{
		if (GM->InitialTurnOrder[i]->Score)
			GM->PlayerScores[i] = GM->InitialTurnOrder[i]->Score;

	}
	//순위 정렬을 위해 TempArray를 만들고
	TArray<int> TempArray;
	TempArray.SetNum(GM->InitialTurnOrder.Num());
	//Initial 의 크기 만큼 Temp크기를 설정하고
	int Count;

	for (int i = 0; i < GM->InitialTurnOrder.Num(); i++)
	{
		Count = 0;
		for (int t = 0; t < GM->InitialTurnOrder.Num(); t++)
		{
			if (GM->PlayerScores[i] < GM->PlayerScores[t])
			{
				Count++;
			}
		}
		TempArray[i] = Count + 1;
	}
	//3번째 playerscore 인덱스의 등수는  temparry3






	for (int t = 0; t < GM->InitialTurnOrder.Num(); t++)
	{
		StatusUi->PersonalState->SetMainScoreText(GM->InitialTurnOrder[t]->Rank);

	}
	*/
}

void APartyGameStateBase::ServerRollDice_Implementation()
{
	MultiRollDice();
}
void APartyGameStateBase::MultiRollDice_Implementation()
{
	CurrentPlayer->RollDice();
}
void APartyGameStateBase::ServerChooseItem_Implementation()
{
	CurrentPlayer->ChooseItem();
}


void APartyGameStateBase::ServerCloseView_Implementation()
{
	MultiCloseView();
}

void APartyGameStateBase::MultiCloseView_Implementation()
{
	ServerRemoveItemUi();
	ServerRemoveSelectUi();
	//ItemUi->RemoveFromParent();
	//SelectUi->RemoveFromParent();
	//현재 플레이어의 턴의 인덱스에 해당하는 플레이어만 사라지게 접근이 필요
	/*
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false;
		PlayerController->bEnableClickEvents = false;

	}
	*/
}

void APartyGameStateBase::ServerClickedGetStarButton_Implementation()
{
	MultiClickedGetStarButton();
}

void APartyGameStateBase::MultiClickedGetStarButton_Implementation()
{
	CurrentPlayer->Score++;
	ServerUpdateGameInfo(PlayerCount);
	//	GM->UpdateGameInfo(PlayerIndex);
	ServerUpdateRankInfo();
	//GM->UpdateRankInfo();
	ServerChangeStarSpace();
	//GM->ChangeStarSpace();


	if (TenCoinsforaStarUi->WrapBox)
	{
		TenCoinsforaStarUi->WrapBox->SetVisibility(ESlateVisibility::Visible);
	}



	// 딜레이 1초
	FTimerHandle DelayTimerHandle;
	float DelayTime = 1;
	bool bIsLoop = false;

	GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, FTimerDelegate::CreateLambda(
		[this]()->void
		{
			TenCoinsforaStarUi->StarImage->SetVisibility(ESlateVisibility::Visible);

			UE_LOG(LogTemp, Warning, TEXT("UTenCoinsforaStar::ClickedButton - Delay"))
				// 별 애니메이션 실행과 동시에 WrapBox랑 버튼 사라짐
				TenCoinsforaStarUi->GetStarAnimation(TenCoinsforaStarUi->StarImageAnimation);

			//Animation 끝나면 자동으로 RemoveWidgetAfterAnimation 실행됨
		}
	), DelayTime, bIsLoop);

}

void APartyGameStateBase::ServerPressPassButton_Implementation()
{
	MultiServerPressPassButton();
}

void APartyGameStateBase::MultiServerPressPassButton_Implementation()
{
	TenCoinsforaStarUi->ServerRemoveWidgetAfterAnimation();
}
void APartyGameStateBase::ServerClickedItem1Button_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Select1"));
	ItemUi->SwitchItem(ItemUi->PlayerInventory[0]);
	//RemoveItemUi(0);
	CurrentPlayer->Inventory[0] = EItem::Nothing;
	MultiClickedItem1Button();
}

void APartyGameStateBase::MultiClickedItem1Button_Implementation()
{
	ServerRemoveItemUi();
	CurrentPlayer->RollDice();

}

void APartyGameStateBase::ServerClickedItem2Button_Implementation()
{
	ItemUi->SwitchItem(ItemUi->PlayerInventory[1]);
	//RemoveItemUi(1);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Select2"));
	CurrentPlayer->Inventory[1] = EItem::Nothing;
	MultiClickedItem2Button();
}

void APartyGameStateBase::MultiClickedItem2Button_Implementation()
{
	ServerRemoveItemUi();
	CurrentPlayer->RollDice();
}

void APartyGameStateBase::DelayTime(float WantSeconds, TFunction<void()> InFunction)
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [InFunction]()
		{
			// 지연 후 실행될 함수 호출
			InFunction();
		}, WantSeconds, false);
}

void APartyGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APartyGameStateBase, PlayerList);
	DOREPLIFETIME(APartyGameStateBase, CurrentPlayerIndex);
	DOREPLIFETIME(APartyGameStateBase, CurrentPlayer);
	DOREPLIFETIME(APartyGameStateBase, TenCoinsforaStarUi);
	DOREPLIFETIME(APartyGameStateBase, Star);
}

