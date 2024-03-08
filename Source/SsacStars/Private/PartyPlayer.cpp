// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyPlayer.h"
#include "BlueBoardSpace.h"
#include "Dice.h"
#include "MainUI.h"
#include "Map_SpaceFunction.h"
#include "PartyGameModeBase.h"
#include "RollDiceCharacter.h"
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

	//이벤트 디스페처 호출
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


	DelayTime(30.0f, [this]()
		{
			if (RollDicePlayer->Dice->IsSelected == false)
			{
				ItemApply();
				RollDicePlayer->CloseView();
			}
		});



}



void APartyPlayer::ItemApply()
{
	//아이템 적용

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
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UseItemWtS"));
				//CurrentSpace=별 전 장소 
			break;
		}
		case EItem::SwitchCharacter:
		{
				//장소 바꾸는 함수 호출
			PlayFun->SwapPlayerPositions(this);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UseItemSC"));
			break;
		}
		case EItem::Nothing:
		{
			//장소 바꾸는 함수 호출 
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("nothing"));
			break;
		}
	}
	
	//PlayFun->SwapPlayerPositions(this);
	DelayTime(2.0f, [this]()
		{
				MoveToSpace(CurrentSpace);

		});
	
}
void APartyPlayer::ChooseItem()
{
	GM->SelectUi->RemoveFromParent();
	GM->AddItemUseUi();


	DelayTime(5.0f, [this]()
		{
			RollDice();
		});
	
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
			// 필요한 경우 AI 컨트롤러 초기화 및 설정
		}
	}

	if (Ai)
	{
		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalActor(CurrentSpace);
		MoveRequest.SetAcceptanceRadius(5.f);
		FNavPathSharedPtr NavPath;

		Ai->MoveToActor(CurrentSpace, 0.1f, false);
		//Ai->MoveTo(MoveRequest, &NavPath, FAIMoveDoneSignature::CreateUObject(this, &APartyPlayer::OnMoveCompleted));

		 
		DelayTime(1.0f,[this]()
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
				
			}
		}
		break;
		case ESpaceState::Trap:
		{
			//함정 위젯 열어서 종류에 따라 실행
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


			DelayTime(2.0f, [this]()
				{
					GM->ChangeStarSpace();
					MoveToSpace(CurrentSpace);

				});

		}
		break;
		case ESpaceState::TwoSideLoad:
		{

		}
		break;
	}


	DelayTime(4.0f, [this]()
		{
			RollDicePlayer->CloseView();
			GM->NextTurn();

		});
	

	


}

void APartyPlayer::StopOrGo()
{
	
	if(CurrentSpace->SpaceState==ESpaceState::Star)
	{
		//별을 먹을건지 물어보고 교환한다
	//먹는다면
		//별의 위치를 바꾼다
		GM->ChangeStarSpace();
		MoveToSpace(CurrentSpace);
	}

	MoveRemaining--;
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
			// 지연 후 실행될 함수 호출
			InFunction();
		}, WantSeconds, false);
}

void APartyPlayer::MyTurnStart()
{


}

void APartyPlayer::MyTurnEnd()
{


}



