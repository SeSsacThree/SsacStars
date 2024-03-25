// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyGameStateBase.h"
#include "MainUI.h"
#include "ThrowDiceCharacterUi.h"
#include "StatusUi.h"
#include "ItemUI.h"
#include "TenCoinsforaStar.h"
#include "PartyGameEnd.h"
#include "Components/Image.h"
#include "TrapWidget.h"
#include "RandomItemWidget.h"
#include "PartyPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "EngineUtils.h"
#include "GetCoins.h"
#include "GetCoins_Pingu.h"
#include "Blueprint/UserWidget.h"
#include "Components/WrapBox.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "CoreMinimal.h"
#include "Dice.h"
#include "GameFramework/Actor.h"
#include "PlayerUiCard.h"
#include "RollDiceCharacter.h"
#include "Components/BoxComponent.h"


APartyGameStateBase::APartyGameStateBase()
{
	/*
	LevelSequence = CreateDefaultSubobject<ULevelSequence>(TEXT("LevelSequence"));
	static ConstructorHelpers::FObjectFinder<ULevelSequence>LS(TEXT("D:/Projects/SsacStars/Content/CJW/PartyGameStart.uasset"));

	if (LS.Succeeded())
	{
		LevelSequence = LS.Object;
	}
	LevelSequenceActor = CreateDefaultSubobject<ALevelSequenceActor>(TEXT("LevelSequenceActor"));
	*/
}

void APartyGameStateBase::BeginPlay()
{
	Super::BeginPlay();
	ThrowDiceUi = NewObject<UThrowDiceCharacterUi>( this , ThrowDiceUiFactory );
	SelectUi = NewObject<UMainUI>(this, SelectUiFactory);
	StatusUi = NewObject<UStatusUi>(this, StatusUiFactory);
	ItemUi = NewObject<UItemUI>(this, ItemUiFactory);
	GetCoinsUi = NewObject<UGetCoins>(this, GetCoinsUiFactory);
	UGetCoins_PinguUi = NewObject<UGetCoins_Pingu>(this, UGetCoins_PinguUiFactory);
	TrapUi = NewObject<UTrapWidget>(this, TrapUiFactory);

	GetItemUi = NewObject<URandomItemWidget>(this, GetItemUiFactory);
	TenCoinsforaStarUi = NewObject<UTenCoinsforaStar>(this, TenCoinsforaStarUiFactory);
	EndGameUi= NewObject<UPartyGameEnd>( this , EndGameUiFactory );
	GM = Cast<APartyGameModeBase>(GetWorld()->GetAuthGameMode());
	Star = Cast<APartyScore>(UGameplayStatics::GetActorOfClass(GetWorld(), APartyScore::StaticClass()));
	Dice = Cast<ADice>( UGameplayStatics::GetActorOfClass( GetWorld() , ADice::StaticClass() ) );
	PlayerScores.SetNum(PlayerList.Num());
	PlayerScores.Init(0, PlayerList.Num());
	
	/*
	FMovieSceneSequencePlaybackSettings Setting;
	Setting.bAutoPlay = false;
	Setting.bPauseAtEnd = true;
	LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, Setting, LevelSequenceActor);
*/

	
		// 서버에서만 실행될 초기화 코드
		// 예: 서버에서 게임 시작 시 시퀀스를 재생하도록 서버에 요청
		if(HasAuthority())
			ServerTriggerSequence();
	
}

void APartyGameStateBase::ServerThrowDiceUi_Implementation()
{
	MultiThrowDiceUi();
}

void APartyGameStateBase::MultiThrowDiceUi_Implementation()
{

		if (ThrowDiceUi)
			ThrowDiceUi->AddToViewport();
	
}

void APartyGameStateBase::ServerViewEndGameUi_Implementation()
{
	MultiViewEndGameUi();
}

void APartyGameStateBase::MultiViewEndGameUi_Implementation()
{
	EndGameUi->AddToViewport();
	EndGameUi->PlayAnimation(EndGameUi->PartyGameEnd );
	DelayTime( 3.0f , [this]()
		{

			EndGameUi->PlayAnimation( EndGameUi->Score );
		} );
}

void APartyGameStateBase::ServerMoveCameraToStar_Implementation()
{
	MultiMoveCameraToStar();

}

void APartyGameStateBase::MultiMoveCameraToStar_Implementation()
{
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	OurPlayerController->SetViewTargetWithBlend(Star, 1.0f);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("StarChange"));
	DelayTime(2.0f, [this]()
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
		Player->GetMesh()->SetWorldScale3D(FVector(22));
		//UPinguAnimInstance* PinguAnimaion = LoadObject<UPinguAnimInstance>(nullptr, TEXT("D:\Projects\SsacStars\Content\JYS\Blueprints"));
		//Player->GetMesh()->GetSkeletalMeshAsset()-
			//SetAnimInstanceClass(PinguAnimaion);
		
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
	
	//StatusUi->PlayAnimation( StatusUi->TurnStartAnimation );
	GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Red , TEXT( "playAnimaion" ) );
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


		//StatusUi->PersonalState->playe = PlayerList[i];
	

	StatusUi->AddToViewport();

}

void APartyGameStateBase::ServerViewItemUi_Implementation()
{
	MultiViewItemUi();
}

void APartyGameStateBase::MultiViewItemUi_Implementation()
{
	ItemUi->AddToViewport();
	//PlaySound()
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
	PlaySound( TrapSound );
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
	if(SelectUi)
	{
		SelectUi->RemoveFromParent();
	}
}

void APartyGameStateBase::ServerRemoveItemUi_Implementation()
{
	MultiRemoveItemUi();
}

void APartyGameStateBase::MultiRemoveItemUi_Implementation()
{
	if(ItemUi)
	{
		ItemUi->RemoveFromParent();
	}
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
	if (FoundSpaces.Num() > 0)
	{
		// 랜덤하게 발판 선택
		ABlueBoardSpace* Space = FoundSpaces[FMath::RandRange( 0 , FoundSpaces.Num() - 1 )];

		// 현재 상태를 이전 상태로 저장
		CurrentPlayer->CurrentSpace->SpaceState = CurrentPlayer->CurrentSpace->PreviousState;

		// 선택된 발판의 이전상태를 최신화
		Space->PreviousState = Space->SpaceState;
		// 선택된 발판을 "Star" 상태로 변경

		Space->SpaceState = ESpaceState::Star;
		GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Red , TEXT( "StarSwitch" ) );
		Space->UpdateAppearance();
	}
	// 그발판이 star,warp 발판이 아니라면
	// 현재 자신의 state를 previousstate에 저장하고
	// star state 상태로 바꾼다


	Star->ReSpace();


}

void APartyGameStateBase::MultiChangeStarSpace_Implementation(ABlueBoardSpace* Space)
{
	//맵상 모든 발판을 검사해서 FOundSpace안에 넣고
	/*
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
	//ServerMoveCameraToStar();

	*/
}


void APartyGameStateBase::ServerUpdateGameInfo_Implementation(int Index)
{
	MultiUpdateGameInfo(Index);
}

void APartyGameStateBase::MultiUpdateGameInfo_Implementation(int Index)
{
	/*
	for (int i = 0; i < PlayerList.Num(); i++)
	{
		if (PlayerList[i]->Score)
			PlayerScores[i] = PlayerList[i]->Score;
	}
	TArray<int> TempArray;
	TempArray.SetNum(PlayerList.Num());
	//Initial 의 크기 만큼 Temp크기를 설정하고
	int Count;

	for (int i = 0; i < PlayerList.Num(); i++)
	{
		Count = 0;
		for (int t = 0; t < PlayerList.Num(); t++)
		{
			if (PlayerScores[i] < PlayerScores[t])
			{
				Count++;
			}
		}
		TempArray[i] = Count + 1;
		PlayerList[i]->Rank = TempArray[i];
	}
	*/
	/*
	if (HasAuthority())
	{
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

	}
	//MultiUpdateRankInfo();
	*/




	switch (Index)
	{
	case 0:
	{
		StatusUi->PersonalState->SetStarScoreText(CurrentPlayer->Score);
		StatusUi->PersonalState->SetSpaceTypeBorder(CurrentPlayer);
		StatusUi->PersonalState->SetMainScoreText(CurrentPlayer->Rank);
		StatusUi->PersonalState->SetTurnOrderScoreText(CurrentPlayerIndex);
		
		break;
	}
	case 1:
	{
		StatusUi->PersonalState1->SetStarScoreText(CurrentPlayer->Score);
		StatusUi->PersonalState1->SetSpaceTypeBorder(CurrentPlayer);
		StatusUi->PersonalState1->SetMainScoreText(CurrentPlayer->Rank);
		StatusUi->PersonalState1->SetTurnOrderScoreText(CurrentPlayerIndex);
		break;
	}
	case 2:
	{
		StatusUi->PersonalState2->SetStarScoreText(CurrentPlayer->Score);
		StatusUi->PersonalState2->SetSpaceTypeBorder(CurrentPlayer);
		StatusUi->PersonalState2->SetMainScoreText(CurrentPlayer->Rank);
		StatusUi->PersonalState2->SetTurnOrderScoreText(CurrentPlayerIndex);
		break;
	}
	case 3:
	{
		StatusUi->PersonalState3->SetStarScoreText(CurrentPlayer->Score);
		StatusUi->PersonalState3->SetSpaceTypeBorder(CurrentPlayer);
		StatusUi->PersonalState3->SetMainScoreText(CurrentPlayer->Rank);
		StatusUi->PersonalState3->SetTurnOrderScoreText(CurrentPlayerIndex);

		break;
	}

	}
	

}
void APartyGameStateBase::ServerUpdateEndInfo_Implementation(int Index)
{
	MultiUpdateEndInfo(Index);
}

void APartyGameStateBase::MultiUpdateEndInfo_Implementation(int Index)
{
	
	switch (Index)
	{
	case 0:
	{
		StatusUi->PersonalState->SetTurnOrderScoreText(CurrentPlayerIndex+1);
		break;
	}
	case 1:
	{

		StatusUi->PersonalState1->SetTurnOrderScoreText(CurrentPlayerIndex+1);
		break;
	}
	case 2:
	{

		StatusUi->PersonalState2->SetTurnOrderScoreText(CurrentPlayerIndex+1);
		break;
	}
	case 3:
	{

		StatusUi->PersonalState3->SetTurnOrderScoreText(CurrentPlayerIndex+1);
		break;
	}

	}
	
}
void APartyGameStateBase::ServerUpdateRankInfo_Implementation()
{
	
}

void APartyGameStateBase::MultiUpdateRankInfo_Implementation()
{
	//현재 플레이어의 인덱스를 넣으면 ex 1
	/*
	StatusUi->PersonalState->SetTurnOrderScoreText(CurrentPlayer->PlayerIndex);
	StatusUi->PersonalState1->SetTurnOrderScoreText(CurrentPlayer->PlayerIndex);
	StatusUi->PersonalState2->SetTurnOrderScoreText(CurrentPlayer->PlayerIndex);
	//	StatusUi->PersonalState3->SetTurnOrderScoreText(CurrentPlayer->PlayerIndex);






	for (int t = 0; t < PlayerList.Num(); t++)
	{
		StatusUi->PersonalState->SetMainScoreText(PlayerList[t]->Rank);

	}
	*/
}

void APartyGameStateBase::ServerRollDice_Implementation()
{
	CurrentPlayer->RollDice();
	MultiRollDice();
}
void APartyGameStateBase::MultiRollDice_Implementation()
{
	
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
	//ServerRemoveItemUi();
	//ServerRemoveSelectUi();

	ItemUi->RemoveFromParent();
	SelectUi->RemoveFromParent();
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

	PlaySound(GetStarSound);

	CurrentPlayer->Score+=50;
	ServerUpdateGameInfo(PlayerCount);
	//	GM->UpdateGameInfo(PlayerIndex);
	//ServerUpdateRankInfo();
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

void APartyGameStateBase::ServerOpenMinigame_Implementation()
{
	DelayTime( 8.0f , [this]()
	{
		MultiOpenMinigame();
	} );
	
	
}

void APartyGameStateBase::MultiOpenMinigame_Implementation()
{
	

	
		// Get the World from this actor
	auto pc = GetWorld()->GetFirstPlayerController();
	FString url = TEXT( "MiniGame_Kart" );
	pc->ClientTravel( url , TRAVEL_Absolute );
	

}
void APartyGameStateBase::ClientTriggerSequence_Implementation()
{
	
	if (SequencePlayer)
	{
		// 시퀀스를 재생합니다.

		SequencePlayer->Play();

		//Controller->SetPause(true);
	}
	
}
void APartyGameStateBase::ServerTriggerSequence_Implementation()
{
	

	MultiTriggerSequence();
}

void APartyGameStateBase::MultiTriggerSequence_Implementation()
{

	Controller = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

	UClass* SequenceActorClass = ALevelSequenceActor::StaticClass();

	// 현재 맵에서 레벨 시퀀스 액터들을 모두 찾습니다.
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), SequenceActorClass, FoundActors);

	// 모든 레벨 시퀀스 액터를 순회하여 시퀀스를 재생합니다.
	for (AActor* FoundActor : FoundActors)
	{
		ALevelSequenceActor* SequenceActor = Cast<ALevelSequenceActor>(FoundActor);
		if (SequenceActor)
		{
			// 시퀀스 액터에 연결된 시퀀스 플레이어를 가져옵니다.
			SequencePlayer = SequenceActor->SequencePlayer;


		}
	}

	if (SequencePlayer)
	{
		// 시퀀스를 재생합니다.

		SequencePlayer->Play();
		ClientTriggerSequence();
		//Controller->SetPause(true);
	}
	
	DelayTime(6.0f, [this]()
		{
			Controller->SetPause(false);
			ServerViewStatusUi();
			ServerSequenceEnded();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CalledMulti"));
		});

	// 시퀀스 액터 찾기
	/*
	if (Controller && LevelSequenceActor)
	{
		// 게임 일시 중지
		Controller->SetPause(true);

		// 시퀀스 재생
		LevelSequencePlayer->Play();
		//auto SequencePlayer = SequenceActor->SequencePlayer;
		//SequencePlayer->Play();
	}
	*/
	
}

void APartyGameStateBase::ServerSequenceEnded_Implementation()
{
	if(HasAuthority())
	{
		GM->InitialRound();
	}

}

void APartyGameStateBase::MultiSequenceEnded_Implementation()
{
}


void APartyGameStateBase::ServerTurnStartUi_Implementation()
{
	MultiTurnStartUi();
}

void APartyGameStateBase::MultiTurnStartUi_Implementation()
{
	StatusUi->PlayAnimation( StatusUi->TurnStartAnimation );
}

void APartyGameStateBase::ServerDiceOverlap_Implementation()
{
	Dice->DicePoint1->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	Dice->DicePoint2->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	Dice->DicePoint3->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	Dice->DicePoint4->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	Dice->DicePoint5->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	Dice->DicePoint6->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	Dice->DiceComp->SetCollisionEnabled( ECollisionEnabled::QueryAndPhysics );
	GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Red , TEXT( "overlapimple" ) );

	//LaunchDice(200);
	Dice->StopRollingLocation = Dice->DiceComp->GetComponentLocation();
	Dice->IsRollingMode = false;
	Dice->IsStopRollingMode = true;
	Dice->IsSelected = true;
	Dice->SetRotationToNumber( Dice->DiceNumber );

	CurrentPlayer->ItemApply();
	//GM->CurrentPlayer->ItemApply();

	CurrentPlayer->RollDicePlayer->CloseView();
	//GM->CurrentPlayer->RollDicePlayer->CloseView();
	MultiDiceOverlap();
}

void APartyGameStateBase::MultiDiceOverlap_Implementation()
{

	GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Red , TEXT( "ServerOverlap" ) );
	
	
}

void APartyGameStateBase::ServerRemoveThrowDiceUi_Implementation()
{
	MultiRemoveThrowDiceUi();
}

void APartyGameStateBase::MultiRemoveThrowDiceUi_Implementation()
{
	if (ThrowDiceUi)
	{
		ThrowDiceUi->RemoveFromParent();
	}
}

void APartyGameStateBase::ServerSoundVoice_Implementation(USoundBase* MySound)
{
	MultiSoundVoice( MySound );
}

void APartyGameStateBase::MultiSoundVoice_Implementation(USoundBase* MySound)
{
	if (MySound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation( this , MySound , CurrentPlayer->GetActorLocation() );
	}
}

void APartyGameStateBase::ServerOverlap_Implementation()
{
	CurrentPlayer->ItemApply();
	CurrentPlayer->RollDicePlayer->CloseView();
}

void APartyGameStateBase::PlaySound(USoundBase* MySound)
{
	if (MySound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation( this , MySound , CurrentPlayer->GetActorLocation() );
	}
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
	DOREPLIFETIME( APartyGameStateBase , ThrowDiceUi );
	DOREPLIFETIME(APartyGameStateBase, Star);
	DOREPLIFETIME(APartyGameStateBase, SequencePlayer);


}

