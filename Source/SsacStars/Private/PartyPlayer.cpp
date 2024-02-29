// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyPlayer.h"
#include "BlueBoardSpace.h"
#include "PartyGameModeBase.h"
#include "RollDiceCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/AIModule/Classes/Navigation/PathFollowingComponent.h"

// Sets default values





APartyPlayer::APartyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void APartyPlayer::BeginPlay()
{
	Super::BeginPlay();

	//이벤트 디스페처 호출
	GM = Cast<APartyGameModeBase>(GetWorld()->GetAuthGameMode());
	RollDicePlayer = Cast<ARollDiceCharacter>(GetWorld());
	Ai = Cast<AAIController>(this->GetController());

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
	OurPlayerController->SetViewTargetWithBlend(this, 0.5f);



	SelectBehavior();
}
void APartyPlayer::SelectBehavior()
{

	
	RollDice();
}
void APartyPlayer::RollDice()
{
	//RollDicePlayer->GetSignal();
	
	MoveRemaining = UKismetMathLibrary::RandomIntegerInRange(1, 6);
	ItemApply();
	MoveToSpace(CurrentSpace);

}
void APartyPlayer::ItemApply()
{
	
}
void APartyPlayer::ChooseItem()
{
	ItemApply();
}


void APartyPlayer::MoveToSpace(ABlueBoardSpace* currentSpace)
{


	if (currentSpace)
	{
		CurrentSpace = currentSpace->NextSpace[0];
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("1move"));
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

		Ai->MoveToActor(CurrentSpace, 5.0f, true);
		//Ai->MoveTo(MoveRequest, &NavPath, FAIMoveDoneSignature::CreateUObject(this, &APartyPlayer::OnMoveCompleted));

		 
		DelayTime(2.0f,[this]()
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

		}
		break;
		case ESpaceState::Red:
		{

		}
		break;
		case ESpaceState::Item:
		{

		}
		break;
		case ESpaceState::Trap:
		{

		}
		break;
		case ESpaceState::Warp:
		{
			
			SetActorLocation(CurrentSpace->WarpSpace->GetActorLocation());
		}
		break;
		case ESpaceState::Star:
		{

		}
		break;
		case ESpaceState::TwoSideLoad:
		{

		}
		break;
	}

	GM->NextTurn();

	UE_LOG(LogTemp, Warning, TEXT("APartyPlayer::MoveEnded - End"))


}

void APartyPlayer::StopOrGo()
{
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



