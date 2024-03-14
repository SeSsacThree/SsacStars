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
		//��ó���� �̴ϼ� �Ͽ��� �� �� player index�� �÷��̾� ���Ե� ���� 0,1,2,3 ����
		InitialTurnOrder[i]->PlayerIndex = i;
		//���� ��û �ʿ� 
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
	//������û�ʿ�
	PartyGameState->ServerMoveCameraToPlayer(CurrentPlayer);

	CurrentPlayer->GetCamera();
	//ChangeStarSpace();

	//��������Ʈ�� nextturn����
}
void APartyGameModeBase::NextTurn()
{

	//CurrentPlayerIndex�� �Ѹ��� �ֻ����� �������� �߰��Ѵ�
	PartyGameState->CurrentPlayerIndex++;
	//CurrentPlayerIndex++;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NextTurn"));

	//���� �÷��� �ϰ� �ִ� �÷��̾��� ����  �ε����� ���� �������� �������� 
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
		//�ٽ� ��ó�� �÷��̾� ���� �ֻ��� ����Ŭ ����
		InitialRound();
	}

	//�̴ϰ��� ���� 
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

	//���� �÷��̾� ���� �ε����� �ش��ϴ� �÷��̾ ������ �ְ� ������ �ʿ�
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
	//���� �÷��̾��� ���� �ε����� �ش��ϴ� �÷��̾ ������� ������ �ʿ�
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false;
		PlayerController->bEnableClickEvents = false;

	}
	*/
}

void APartyGameModeBase::ChangeStarSpace()
{
	//���� ���ӽ����Ҷ� ȣ��������� 
	//�ʻ��� ��� �����߿��� �ϳ��� ���

	// UClass�� ���� ���͸��� Ŭ������ ����

	/*
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
	*/
	PartyGameState->ServerChangeStarSpace();
}
/*
void APartyGameModeBase::AddTrapUi()
{
	TrapUi->AddToViewport();
	���� �� ��ȯ�ʿ�
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
		//���� �÷��̾��� �ε����� ������ ex 1
		StatusUi->PersonalState->SetTurnOrderScoreText(CurrentPlayer->PlayerIndex);
		StatusUi->PersonalState1->SetTurnOrderScoreText(CurrentPlayer->PlayerIndex);
		StatusUi->PersonalState2->SetTurnOrderScoreText(CurrentPlayer->PlayerIndex);
	//	StatusUi->PersonalState3->SetTurnOrderScoreText(CurrentPlayer->PlayerIndex);

		//�÷��̾� ����� ����ִ� �� ���ھ �����Ͽ� �÷��̾� ���ڿ�����
		for(int i=0;i<InitialTurnOrder.Num();i++ )
		{
			if(InitialTurnOrder[i]->Score)
				PlayerScores[i] = InitialTurnOrder[i]->Score;

		}
	//���� ������ ���� TempArray�� �����
		TArray<int> TempArray;
		TempArray.SetNum(InitialTurnOrder.Num());
	//Initial �� ũ�� ��ŭ Tempũ�⸦ �����ϰ�
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
		//3��° playerscore �ε����� �����  temparry3






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
		// ������ �Ͻ������մϴ�.
		PlayerController->SetPause(true);
	}
}

void APartyGameModeBase::GameRelease()
{
	if (PlayerController)
	{
		// ������ �Ͻ������մϴ�.
		PlayerController->SetPause(false);
	}
}



