// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyPlayer.h"
#include "BlueBoardSpace.h"

#include "MainUI.h"
#include "Map_SpaceFunction.h"
#include "PartyGameModeBase.h"
#include "PlayerUiCard.h"
#include "RollDiceCharacter.h"
#include "StatusUi.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/AIModule/Classes/Navigation/PathFollowingComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
// Sets default values





APartyPlayer::APartyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DiceRemainWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DiceRemainWidget"));
	DiceRemainWidget->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void APartyPlayer::BeginPlay()
{
	Super::BeginPlay();

	//�̺�Ʈ ����ó ȣ��
	GM = Cast<APartyGameModeBase>(GetWorld()->GetAuthGameMode());
	RollDicePlayer = Cast<ARollDiceCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ARollDiceCharacter::StaticClass()));
	Ai = Cast<AAIController>(this->GetController());
	PlayFun = Cast<AMap_SpaceFunction>(UGameplayStatics::GetActorOfClass(GetWorld(), AMap_SpaceFunction::StaticClass()));
	Inventory.SetNum(MaxInventorySize);
	Inventory.Init(EItem::Nothing, MaxInventorySize);
	ToApplyDo = EItem::Nothing;
	
}

// Called every frame
void APartyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	
	

	
}

// Called to bind functionality to input
void APartyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



void APartyPlayer::GetCamera()
{
	
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	OurPlayerController->SetViewTargetWithBlend(this, 1.0f);

	DelayTime(1.0f, [this]()
		{
			SelectBehavior();
		});


	
}
void APartyPlayer::SelectBehavior()
{
	GM->AddSelectBehaviorUi();

}
void APartyPlayer::RollDice()
{
	//RollDicePlayer->GetSignal();
	
	//MoveRemaining = UKismetMathLibrary::RandomIntegerInRange(1, 6);
	

	GM->CloseView();
	RollDicePlayer->AddView();
	RollDicePlayer->GetSignal();
	DelayTime(2.0f, [this]()
		{
			RollDicePlayer->StartRolling();
		});






}



void APartyPlayer::ItemApply()
{
	//������ ����

	switch (ToApplyDo)
	{
		case EItem::Add3Dice:
			{
				MoveRemaining += 3;
				
				PlayFun->PlusThreeSpaces(this);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UseItema3d"));
				break;
			}
		case EItem::WarpToStar:
		{
			CurrentSpace = GM->Star->StarSpace;
			SetActorLocation(CurrentSpace->GetActorLocation(), false, nullptr, ETeleportType::TeleportPhysics);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UseItemWtS"));
				//CurrentSpace=�� �� ��� 
			break;
		}
		case EItem::SwitchCharacter:
		{
				//��� �ٲٴ� �Լ� ȣ��
			PlayFun->SwapPlayerPositions(this);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UseItemSC"));
			break;
		}
		case EItem::Nothing:
		{
			//��� �ٲٴ� �Լ� ȣ��
			
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("nothing"));
			break;
		}
	}
	
	//PlayFun->SwapPlayerPositions(this);
	
	DelayTime(2.0f, [this]()
		{
				RollDicePlayer->CloseView();
				MoveToSpace(CurrentSpace);

		});
	
	
}
void APartyPlayer::ChooseItem()
{
	GM->SelectUi->RemoveFromParent();
	GM->AddItemUseUi();

	/*
	DelayTime(5.0f, [this]()
		{
			RollDice();
		});
	*/
}


void APartyPlayer::MoveToSpace(ABlueBoardSpace* currentSpace)
{


	if (currentSpace)
	{
		CurrentSpace = currentSpace->NextSpace[0];


	}


		
	if (!Ai)
	{
		Ai = Cast<AAIController>(this->GetController());
		if (!Ai)
		{
			Ai = GetWorld()->SpawnActor<AAIController>();
			// �ʿ��� ��� AI ��Ʈ�ѷ� �ʱ�ȭ �� ����
		}
	}

	if (Ai)
	{
		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalActor(CurrentSpace);
		MoveRequest.SetAcceptanceRadius(5.f);
		FNavPathSharedPtr NavPath;

		Ai->MoveToActor(CurrentSpace, 5.0f, true);
		//Ai->MoveTo(MoveRequest, &NavPath, FAIMoveDoneSignature::CreateUObject(this, &APartyPlayer::OnMoveCompleted));

		 
		DelayTime(1.5f,[this]()
		{
				StopOrGo();
		});


		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PlayerMove"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PlayerCantMove"));
	}

	
	
} 

void APartyPlayer::MoveEnded()
{
	
	UE_LOG(LogTemp, Warning, TEXT("APartyPlayer::MoveEnded - Start"))

	switch (CurrentSpace->SpaceState)
	{
		case ESpaceState::Blue:
		{
			Coin += 3;
		}
		break;
		case ESpaceState::Red:
		{
			Coin -= 3;
		}
		break;
		case ESpaceState::Item:
		{
			GM->AddGetItemUi();
			int RanItemNum = UKismetMathLibrary::RandomIntegerInRange(1, 3);

			UE_LOG(LogTemp, Warning, TEXT("APartyPlayer::ItemSpace"))
			if(Inventoryindex<3)
			{
				switch (RanItemNum)
				{
					case 1:
						{

							Inventory[Inventoryindex] = EItem::Add3Dice;
							GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("a3d"));
							//GM->ItemUi->Add3DiceItem();
							break;
						}
				case 2:
					{
						Inventory[Inventoryindex] = EItem::WarpToStar;
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("wts"));
							//GM->ItemUi->WarpToStarItem();
						break;
					}
					case 3:
					{
						Inventory[Inventoryindex] = EItem::SwitchCharacter;
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("sw"));
						//GM->ItemUi->SwitchSpaceItem();
						break;
					}
				}
				
				Inventoryindex++;
				
			}
			else
			{
				for(int i=0;i<Inventoryindex;i++)
				{
					if(Inventory[i]==EItem::Nothing)
					{


						switch (RanItemNum)
						{
							case 1:
							{

								Inventory[i] = EItem::Add3Dice;
								GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("a3d"));
								//GM->ItemUi->Add3DiceItem();
								break;
							}
							case 2:
							{
								Inventory[i] = EItem::WarpToStar;
								GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("wts"));
								//GM->ItemUi->WarpToStarItem();
								break;
							}
							case 3:
							{
								Inventory[i] = EItem::SwitchCharacter;
								GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("sw"));
								//GM->ItemUi->SwitchSpaceItem();
								break;
							}
						}
						
							

					}
				}
				
			}
		}
		break;
		case ESpaceState::Trap:
		{
			//���� ���� ��� ������ ���� ����
			GM->AddTrapUi();
		}
		break;
		case ESpaceState::Warp:
		{
			//AMap_SpaceFunction Map_SpaceFunction;
			//Map_SpaceFunction.SwapPlayerPositions(this);
			
			SetActorLocation(CurrentSpace->WarpSpace->GetActorLocation());
		}
		break;
		case ESpaceState::Star:
		{
			
			GM->AddTenCoinsforaStar();
			GetStar();
			//������ �ð��� ������ �ڵ����� ������ ������ ������ ������ �ٲ����
		}
		break;
		case ESpaceState::TwoSideLoad:
		{

		}
		break;
	}
	MyInfoSend();

	DelayTime(4.0f, [this]()
		{
			RollDicePlayer->CloseView();
			MyTurnEnd();
			GM->NextTurn();

		});
	

	


}

void APartyPlayer::StopOrGo()
{

	MoveRemaining--;

	if(CurrentSpace->SpaceState==ESpaceState::Star)
	{
		GM->AddTenCoinsforaStar();
		GM->GamePause();
		//������ �����ִµ��� �׳� ������ �귯���� ������ ���ƾ��� 
	}


	if (MoveRemaining > 0)
	{
		MoveToSpace(CurrentSpace);
	}
	else
	{
		MoveEnded();
	}
}

void APartyPlayer::DelayTime(float WantSeconds,TFunction<void()> InFunction)
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [InFunction]()
		{
			// ���� �� ����� �Լ� ȣ��
			InFunction();
		}, WantSeconds, false);
}

void APartyPlayer::MyTurnStart()
{


}

void APartyPlayer::MyTurnEnd()
{
	
	
	if(PlayerIndex>=0)
	{
	GM->PlayerCoins[PlayerIndex] =Coin;
	GM->PlayerCoins[PlayerIndex] =Score;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MYSCoreSEND"));
	}

}

void APartyPlayer::MyInfoSend()
{
	switch (PlayerIndex)
	{
		case 0:
			{
				GM->StatusUi->PersonalState->SetCoinScoreText(Coin);
				GM->StatusUi->PersonalState->SetStarScoreText(Score);
				GM->StatusUi->PersonalState->SetSpaceTypeBorder(this);
				GM->StatusUi->PersonalState1->SetMainScoreText(Rank);
				break;
			}	
		case 1:
		{
			GM->StatusUi->PersonalState1->SetCoinScoreText(Coin);
			GM->StatusUi->PersonalState1->SetStarScoreText(Score);
			GM->StatusUi->PersonalState1->SetSpaceTypeBorder(this);
			GM->StatusUi->PersonalState1->SetMainScoreText(Rank);
			break;

		}
		case 2:
		{
			GM->StatusUi->PersonalState2->SetCoinScoreText(Coin);
			GM->StatusUi->PersonalState2->SetStarScoreText(Score);
			GM->StatusUi->PersonalState2->SetSpaceTypeBorder(this);
			GM->StatusUi->PersonalState1->SetMainScoreText(Rank);
			break;
			
		}
		case 3:
		{
			GM->StatusUi->PersonalState3->SetCoinScoreText(Coin);
			GM->StatusUi->PersonalState3->SetStarScoreText(Score);
			GM->StatusUi->PersonalState3->SetSpaceTypeBorder(this);
			GM->StatusUi->PersonalState1->SetMainScoreText(Rank);
			break;
		
		}
	}


	GM->PlayerCoins[PlayerIndex] = Coin;
	GM->PlayerScores[PlayerIndex] = Score;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("MyVariable: %d"), PlayerIndex));
}

void APartyPlayer::GetStar()
{
	
	//���� �������� ����� ��ȯ�Ѵ�
//�Դ´ٸ�
	//���� ��ġ�� �ٲ۴�
	auto BeforeChangeSpace = CurrentSpace;
	MyInfoSend();
	GM->ChangeStarSpace();
	//MoveToSpace(BeforeChangeSpace);

}



