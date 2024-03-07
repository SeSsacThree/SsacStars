// Fill out your copyright notice in the Description page of Project Settings.
#include "PartyGameModeBase.h"
#include "PartyPlayer.h"
#include "MainUI.h"
#include "StatusUi.h"
#include "ItemUI.h"
#include "TenCoinsforaStar.h"
#include "PlayerUiCard.h"
#include "TrapWidget.h"
#include "RandomItemWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "EngineUtils.h"
#include "PartyController.h"
#include "PartyScore.h"

APartyGameModeBase::APartyGameModeBase()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh1(TEXT("/Script/Engine.SkeletalMesh'/Game/CJW/Models/ZZang/Shinchan_Models.Shinchan_Models'"));
	if(tempMesh1.Succeeded())
	{
		Mesh1 = tempMesh1.Object;
	}
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh2(TEXT("/Script/Engine.SkeletalMesh'/Game/KMS/Mesh/pingu/pingu.pingu'"));
	if (tempMesh2.Succeeded())
	{
		Mesh2 = tempMesh2.Object;
	}
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh3(TEXT("/Script/Engine.SkeletalMesh'/Game/JYS/Kirby/source/kirby.kirby'"));
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
	PlayerSetting();
	//SelectUi = CreateWidget<UMainUI>(GetWorld(), SelectUiFactory);
	SelectUi = NewObject<UMainUI>(this, SelectUiFactory);
	StatusUi = NewObject<UStatusUi>(this, StatusUiFactory);
	ItemUi = NewObject<UItemUI>(this, ItemUiFactory);
	TrapUi= NewObject<UTrapWidget>(this, TrapUiFactory);
	GetItemUi = NewObject<URandomItemWidget>(this, GetItemUiFactory);
	PlayerUiCard = NewObject<UPlayerUiCard>(this, PlayerUiCardFactory);
	TenCoinsforaStarUi = NewObject<UTenCoinsforaStar>(this, TenCoinsforaStarUiFactory);
	//������ ���ϰ� ������ �ǵ�� ��
	//Algo::Shuffle(InitialTurnOrder);
	StatusUi->AddToViewport();
	
	InitialRound();
}


void APartyGameModeBase::PlayerSetting()
{
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

	InitialTurnOrder = TurnOrder;

	for (int i = 0; i < InitialTurnOrder.Num(); i++)
	{
		InitialTurnOrder[i]->PlayerIndex = i;
		SetPlayerAppeareance(InitialTurnOrder[i], i);
	}
	
	PlayerCoins.SetNum(InitialTurnOrder.Num());
	PlayerCoins.Init(0, InitialTurnOrder.Num());
	PlayerScores.SetNum(InitialTurnOrder.Num());
	PlayerScores.Init(0, InitialTurnOrder.Num());
}

void APartyGameModeBase::SetPlayerAppeareance(APartyPlayer*Player,int Index)
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

void APartyGameModeBase::AddItemUseUi()
{
	ItemUi->AddToViewport();
	

}
void APartyGameModeBase::InitialRound()
{
	RoundOrder = InitialTurnOrder;

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
	UpdateGameInfo();

}

void APartyGameModeBase::AddTrapUi()
{
	TrapUi->AddToViewport();
	
}

void APartyGameModeBase::AddGetItemUi()
{
	GetItemUi->AddToViewport();
}

void APartyGameModeBase::AddTenCoinsforaStar()
{
	TenCoinsforaStarUi->AddToViewport();
}

void APartyGameModeBase::UpdateGameInfo()
{
	int MaxTemp = 0;
	int Rank=1;
	int PreviousScore = 9999;
	for (int t = 0; t < InitialTurnOrder.Num(); t++)
	{
		for (int i = 0; i < InitialTurnOrder.Num(); i++)
		{
			if (PlayerCoins[i] >= MaxTemp&&PlayerCoins[i]<PreviousScore)
			{
				MaxTemp = PlayerCoins[i];
				Rank = i;
				InitialTurnOrder[i]->Rank = Rank;
			}
		}
		PreviousScore = MaxTemp;
		Rank++;
		MaxTemp = 0;
	}
}

void APartyGameModeBase::GamePause()
{

	 PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (PlayerController)
	{
		// ������ �Ͻ������մϴ�.
		PlayerController->SetPause(true);
	}
}



