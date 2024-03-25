// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyPlayer.h"
#include "BlueBoardSpace.h"
#include "Dice.h"
#include "StatusUi.h"
#include "ItemUi.h"
#include "MainUi.h"
#include "Map_SpaceFunction.h"
#include "PartyGameModeBase.h"
#include "RollDiceCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/AIModule/Classes/Navigation/PathFollowingComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "PartyGameStateBase.h"
#include "Net/UnrealNetwork.h"
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
	PartyGameState = Cast<APartyGameStateBase>(GetWorld()->GetGameState());
	//PartyGameState = GetGameState<APartyGameStateBase>();
	RollDicePlayer = Cast<ARollDiceCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ARollDiceCharacter::StaticClass()));
	Ai = Cast<AAIController>(this->GetController());
	PlayFun = Cast<AMap_SpaceFunction>(UGameplayStatics::GetActorOfClass(GetWorld(), AMap_SpaceFunction::StaticClass()));
	Inventory.SetNum(MaxInventorySize);
	Inventory.Init(EItem::Nothing, MaxInventorySize);
	ToApplyDo = EItem::Nothing;
	//PartyGameState->ServerTriggerSequence();
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


void APartyPlayer::ServerChangeAppereance_Implementation()
{
	MultiChangeAppereance();

}

void APartyPlayer::MultiChangeAppereance_Implementation()
{

}

void APartyPlayer::GetCamera()
{


	//APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	//OurPlayerController->SetViewTargetWithBlend(this, 1.0f);
	PartyGameState->ServerTurnStartUi();
	DelayTime(1.0f, [this]()
		{
			SelectBehavior();
		});



}
void APartyPlayer::SelectBehavior()
{
	//GM->AddSelectBehaviorUi();
	PartyGameState->ServerUpdateGameInfo(PlayerIndex);
	PartyGameState->ServerViewSelectUi();
}
void APartyPlayer::RollDice()
{
	//RollDicePlayer->GetSignal();

	//MoveRemaining = UKismetMathLibrary::RandomIntegerInRange(1, 6);

	PartyGameState->ServerCloseView();

	if(HasAuthority())
		UE_LOG( LogTemp , Warning , TEXT( "RemainRollDice" ) );

	
	//RollDicePlayer->AddView();
	//RollDicePlayer->ServerViewThrowDiceUi();
	PartyGameState->ServerThrowDiceUi();
	UE_LOG( LogTemp , Warning , TEXT( "	RollDicePlayer->ServerViewThrowDiceUi();" ) );
	if(HasAuthority())
		RollDicePlayer->GetSignal();
	UE_LOG( LogTemp , Warning , TEXT( "	RollDicePlayer->GetSignal();" ) );
	DelayTime(2.0f, [this]()
		{
			RollDicePlayer->StartRolling();

		});

	/*
	DelayTime(30.0f, [this]()
		{
			if (RollDicePlayer->Dice->IsSelected == false)
			{
				ItemApply();
				RollDicePlayer->CloseView();
			}
		});
		*/


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
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UseItema3d"));
		break;
	}
	case EItem::WarpToStar:
	{
		FVector TelpLocation = GetActorLocation();
		TelpLocation.Z += 100;
		SetActorLocation(TelpLocation);
		CurrentSpace = GM->Star->StarSpace;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UseItemWtS"));
		//CurrentSpace=별 전 장소 
		break;
	}
	case EItem::SwitchCharacter:
	{
		//장소 바꾸는 함수 호출
		PlayFun->SwapPlayerPositions(this);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UseItemSC"));
		break;
	}
	case EItem::Nothing:
	{
		//장소 바꾸는 함수 호출 
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("nothing"));
		break;
	}
	}
	MoveRemaining += 3;


	DelayTime(2.0f, [this]()
		{
			MoveToSpace(CurrentSpace);

		});

}
void APartyPlayer::ChooseItem()
{
	PartyGameState->ServerRemoveSelectUi();
	//	GM->SelectUi->RemoveFromParent();
		//GM->AddItemUseUi();
	PartyGameState->ServerViewItemUi();

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
		// 이동 하고 
		FAIMoveRequest MoveRequest;
		FVector MoveLoc = CurrentSpace->GetActorLocation();
		MoveLoc.Y -=20;
		MoveRequest.SetGoalLocation(MoveLoc);
		//MoveRequest.SetGoalActor(CurrentSpace);
		MoveRequest.SetAcceptanceRadius(0.1f);
		FNavPathSharedPtr NavPath;
		FAIMoveCompletedSignature Move;
		//Ai->MoveToActor(CurrentSpace, 0.1f, false);
		Ai->MoveTo(MoveRequest, &NavPath);

		//1초후에 멈춰라 
		DelayTime(1.0f, [this]()
			{
				StopOrGo();
			});


		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PlayerMove"));
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PlayerCantMove"));
	}



}

void APartyPlayer::MoveEnded()
{

	UE_LOG(LogTemp, Warning, TEXT("APartyPlayer::MoveEnded - Start"))

		switch (CurrentSpace->SpaceState)
		{
		case ESpaceState::Blue:
		{
			//Coin += 3;
			PartyGameState->PlaySound( PartyGameState->BlueSpaceSound );
			Score += 20;
			PartyGameState->ServerGetCoinsUi();
		}
		break;
		case ESpaceState::Red:
		{
			PartyGameState->PlaySound( PartyGameState->RedSpaceSound );
			PartyGameState->ServerGetCoins_PinguUi();
			//Coin -= 3;
			Score -= 20;
		}
		break;
		case ESpaceState::Item:
		{


			int RanItemNum = UKismetMathLibrary::RandomIntegerInRange(1, 3);
			PartyGameState->PlaySound( PartyGameState->ItemSound );
			UE_LOG(LogTemp, Warning, TEXT("APartyPlayer::ItemSpace"))
				if (Inventoryindex < 3)
				{
					switch (RanItemNum)
					{
					case 1:
					{

						Inventory[Inventoryindex] = EItem::Add3Dice;
					//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("a3d"));
						//GM->ItemUi->Add3DiceItem();
						break;
					}
					case 2:
					{
						Inventory[Inventoryindex] = EItem::WarpToStar;
						//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("wts"));
						//GM->ItemUi->WarpToStarItem();
						break;
					}
					case 3:
					{
						Inventory[Inventoryindex] = EItem::SwitchCharacter;
						//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("sw"));
						//GM->ItemUi->SwitchSpaceItem();
						break;
					}
					}

					Inventoryindex++;

				}
				else
				{
					//일단 아이템 두개만 보유 	
				}
		}
		break;
		case ESpaceState::Trap:
		{
			//함정 위젯 열어서 종류에 따라 실행
			//GM->AddTrapUi();
			PartyGameState->ServerViewTrapUi();
			PartyGameState->PlaySound( PartyGameState->TrapSound );
			
				DelayTime( 2.0f , [this]()
				{

					int RandTrap = UKismetMathLibrary::RandomIntegerInRange( 0 , 2 );

					ApplyTrap( RandTrap );

				} 
				
				);
		}
		break;
		case ESpaceState::Warp:
		{
			//AMap_SpaceFunction Map_SpaceFunction;
			//Map_SpaceFunction.SwapPlayerPositions(this);
			PartyGameState->ServerSoundVoice( PartyGameState->WarpSound );
			FVector TelpLoc = CurrentSpace->WarpSpace->GetActorLocation();

			TelpLoc.Z += 1000;
			SetActorLocation( TelpLoc );
			SetActorRotation( FRotator( 0 ) );
			CurrentSpace = CurrentSpace->WarpSpace;
		}
		break;
		case ESpaceState::Star:
		{

			// 최종 도착이 별이여도 그냥 한칸 더 간다 
			PartyGameState->ServerViewTenCoinsforaStarUi();
				//교환 할거냐 물어보기 

			DelayTime(4.0f, [this]()
				{
					PartyGameState->ServerChangeStarSpace();
					//GM->ChangeStarSpace();
						DelayTime( 2.0f , [this]()
						{
							MoveToSpace(CurrentSpace);
						} );
				});

		}
		break;
		case ESpaceState::TwoSideLoad:
		{

		}
		break;
		}

	//발판에 대한 특성 적용 시간
	if (CurrentSpace->SpaceState != ESpaceState::Star && MoveRemaining <= 0)
	{
		DelayTime(4.0f, [this]()
			{
				RollDicePlayer->CloseView();

				if (true == IsLocallyControlled())
				{

					FAIMoveRequest MoveRequest;
					FVector MoveLoc = CurrentSpace->GetActorLocation();
					//MoveLoc.X += 150;
					MoveLoc.Y += 150;
					MoveRequest.SetGoalLocation( MoveLoc );
					//MoveRequest.SetGoalActor(CurrentSpace);
					MoveRequest.SetAcceptanceRadius( 0.1f );
					FNavPathSharedPtr NavPath;
					FAIMoveCompletedSignature Move;
					//Ai->MoveToActor(CurrentSpace, 0.1f, false);
					Ai->MoveTo( MoveRequest , &NavPath );
					PartyGameState->StatusUi->PlayAnimation( PartyGameState->StatusUi->TurnEndAnimation );
					
					DelayTime( 4.0f , [this]()
					{
						PartyGameState->ServerUpdateGameInfo( PlayerIndex );
						PartyGameState->ServerUpdateEndInfo( PlayerIndex );
						GM->NextTurn();
					});


				}

				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("End"));
			});
	}




}

void APartyPlayer::StopOrGo()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("StopOrGo"));

	//중간 멈춤 장소가 별이라면 , 
	if (CurrentSpace->SpaceState == ESpaceState::Star)
	{
		//별을 먹을건지 물어보고 교환한다
	//먹는다면
		//별의 위치를 바꾼다

		PartyGameState->ServerViewTenCoinsforaStarUi();
		//PartyGameState->ServerChangeStarSpace();

	}

	//중간멈춤 장소가 별이 아닌데 주사위가 남으면 앞으로 
	if (CurrentSpace->SpaceState != ESpaceState::Star && MoveRemaining > 0)
	{
		MoveRemaining--;
		MoveToSpace(CurrentSpace);
	}//별이아닌데 주사위가 없으면 멈춰
	else if (CurrentSpace->SpaceState != ESpaceState::Star && MoveRemaining == 0)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CallMoveEnded"));
		PartyGameState->ServerUpdateGameInfo(PlayerIndex);
		//	GM->UpdateGameInfo(PlayerIndex);
		//	GM->UpdateRankInfo();
		//PartyGameState->ServerUpdateRankInfo();

		MoveEnded();
	}
}

void APartyPlayer::ApplyTrap(int Index)
{
	switch (Index)
	{
		case 0:
			{
				Score -= 30;
				break;
			}
		case 1:
			{
				Score /= 2;
				break;
			}
		case 2:
			{
				Score = 0;
				break;
			}
	}
	PartyGameState->ServerUpdateGameInfo( PlayerIndex );
}

void APartyPlayer::DelayTime(float WantSeconds, TFunction<void()> InFunction)
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

void APartyPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME( APartyPlayer , MoveRemaining );
	DOREPLIFETIME( APartyPlayer , PlayerIndex );
	DOREPLIFETIME( APartyPlayer , RollDicePlayer );
	DOREPLIFETIME( APartyPlayer , DiceRemainWidget );
	
}



