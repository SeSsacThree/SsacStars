// Fill out your copyright notice in the Description page of Project Settings.


#include "KartPlayer.h"

#include "EndingWidget.h"
#include "EngineUtils.h"
#include "ItemBox.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "ItemWidget.h"
#include "KartGameState.h"
#include "KartPlayerController.h"
#include "KartPlayerState.h"
#include "MiniGameBullet.h"
#include "MiniGameMainUI.h"
#include "Star.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Components/PrimitiveComponent.h"
#include "TimerManager.h"
#include "Camera/CameraActor.h"
#include "Components/ArrowComponent.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AKartPlayer::AKartPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	playerMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("playerMeshComp"));
	playerMeshComp->SetupAttachment(RootComponent);
	playerMeshComp->SetRelativeLocation(FVector(30.836835, 28.841, -38.838));
	playerMeshComp->SetRelativeRotation(FRotator(0, -90, 0));
	playerMeshComp->SetRelativeScale3D(FVector(0.3f));
	playerMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	carMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("carMeshComp"));
	carMeshComp->SetupAttachment(RootComponent);
	carMeshComp->SetRelativeLocation(FVector(0, 30, -79));
	carMeshComp->SetRelativeRotation(FRotator(0, -90, 90));
	carMeshComp->SetRelativeScale3D(FVector(100));
	carMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetWorldLocation(FVector(0, -800, 577));
	springArmComp->SetWorldRotation(FRotator(-12, 90, 0));
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraComp"));
	cameraComp->SetupAttachment(springArmComp);

	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("firePosition"));
	// 루트에 붙이고싶다.
	firePosition->SetupAttachment(RootComponent);


	UCapsuleComponent* PlayerCapsule = GetCapsuleComponent();
	PlayerCapsule->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AKartPlayer::BeginPlay()
{
	Super::BeginPlay();

	InitializeWidgets();
}

void AKartPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitializeWidgets();
}

void AKartPlayer::InitializeWidgets()
{
	AKartPlayerController* pc = Cast<AKartPlayerController>(GetController());

	if(nullptr == pc || false == IsLocallyControlled())
	{
		return;
	}

	
	if(nullptr == pc->itemUI)
	{
		pc->itemUI = CreateWidget<UItemWidget>(GetWorld(), itemUIFactory);
		pc->itemUI->AddToViewport();
	}
	itemUI = pc->itemUI;

	if (nullptr == pc->MainUI)
	{
		pc->MainUI = CreateWidget<UMiniGameMainUI>(GetWorld(), MainUIFactory);
		pc->MainUI->AddToViewport();
	}
	MainUI = pc->MainUI;

	for (TActorIterator<AItemBox> it(GetWorld()); it; ++it)
	{
		AItemBox* box = *it;
		box->itemWidget = itemUI;
		break;			
	}

	for (TActorIterator<AStar> it(GetWorld()); it; ++it)
	{
		AStar* star = *it;
		star->mainUI = MainUI;
	}


	starCount = 0;
	StarCountText = FText::FromString(FString::FromInt(starCount));
	MainUI->StarCount->SetText(StarCountText);
}

// Called every frame
void AKartPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bSpeedUp)
	{
		currentTime += GetWorld()->GetDeltaSeconds();

		LaunchCharacter(GetActorForwardVector() * 5000, true, true);

		if (currentTime > speedUpTime)
		{
			speedDown();
			currentTime = 0;
		}
	}
}


// Called to bind functionality to input
void AKartPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Horizontal", this, &AKartPlayer::MoveForward);
	PlayerInputComponent->BindAxis("Vertical", this, &AKartPlayer::TurnRight);
	PlayerInputComponent->BindAction(TEXT("Item"), IE_Pressed, this, &AKartPlayer::useItem);
}

void AKartPlayer::MoveForward(float Value)
{
	if(!isPaused)
	{
		ServerMoveForward(Value);
	}
}
void AKartPlayer::ServerMoveForward_Implementation(float Value)
{
	MultiMoveForward(Value);
}

void AKartPlayer::MultiMoveForward_Implementation(float Value)
{
	AddMovementInput(this->GetActorForwardVector(), Value);
}



void AKartPlayer::TurnRight(float Value)
{
	if (!isPaused)
	{
		ServerTurnRight(Value);
	}
}
void AKartPlayer::ServerTurnRight_Implementation(float Value)
{
	MultiTurnRight(Value);
}
void AKartPlayer::MultiTurnRight_Implementation(float Value)
{
	FRotator NewRotation = this->GetActorRotation();
	NewRotation.Yaw -= Value;
	this->SetActorRotation(NewRotation);
}



void AKartPlayer::Boost()
{
	ServerBoost();
}
void AKartPlayer::ServerBoost_Implementation()
{
	MultiBoost();
}

void AKartPlayer::MultiBoost_Implementation()
{
	bSpeedUp = true;
}
//---------------------------------------------------------------------------------------


void AKartPlayer::OnRep_UpdateStarCountUI()
{
	StarCountText = FText::FromString( FString::FromInt( starCount ) );
	if (MainUI && MainUI->StarCount)
	{
		MainUI->StarCount->SetText( StarCountText );
		UE_LOG( LogTemp , Warning , TEXT( " AKartPlayer::OnRep_UpdateStarCountUI()" ) );
	}
	else
	{
		UE_LOG( LogTemp , Warning , TEXT( " AKartPlayer::OnRep_UpdateStarCountUI() - NO UI" ) );
	}
}

void AKartPlayer::ServerSetStarCount_Implementation(int32 InStarCount)
{
	starCount = starCount + InStarCount;
	
	UE_LOG( LogTemp , Warning , TEXT( "AKartPlayer::ServerSetStarCount : %d 개"  ) , starCount );
	//PlayerState에 점수 저장
	auto ps = Cast<AKartPlayerController>( Controller )->GetPlayerState<AKartPlayerState>();
	ps->SetScore( starCount );
	//서버에서는 자동 호출이 안되기 때문에 직접 호출
	OnRep_UpdateStarCountUI();

}

void AKartPlayer::useItem()
{
	//플레이어가 아이템이 있을 때만 사용 가능
	if (hasItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("USE ITEM"));
		itemUI->Init();
		hasItem = false;
		ServeUseItem();
	}

}
void AKartPlayer::ServeUseItem_Implementation()
{
	MultiUseItem();
}
void AKartPlayer::MultiUseItem_Implementation()
{
	switch (itemNumber)
	{
	case 1:
		speedUp();
		break;
	case 2:
		shoot();
		break;

	}
}

//---------------------------------------------------------------------------------------

void AKartPlayer::speedUp()
{
	ServerSpeedUp();
	UGameplayStatics::PlaySound2D( GetWorld() , speedSound );
}

void AKartPlayer::ServerSpeedUp_Implementation()
{
	MultiSpeedUp();
}


void AKartPlayer::MultiSpeedUp_Implementation()
{
	bSpeedUp = true;
}

//---------------------------------------------------------------------------------------

void AKartPlayer::speedDown()
{
	ServerSpeedDown();
}
void AKartPlayer::ServerSpeedDown_Implementation()
{
	MultiSpeedDown();
}

void AKartPlayer::MultiSpeedDown_Implementation()
{
	bSpeedUp = false;
	//GetCharacterMovement()->Velocity = GetCharacterMovement()->Velocity * 0.5f;
}


//---------------------------------------------------------------------------------------

void AKartPlayer::shoot()
{
	ServerShoot();
	UGameplayStatics::PlaySound2D( GetWorld() , shootingSound );
}



void AKartPlayer::ServerShoot_Implementation()
{
	FTransform t = firePosition->GetComponentTransform();
	GetWorld()->SpawnActor<AMiniGameBullet>( bulletFactory , t );
	UE_LOG( LogTemp , Warning , TEXT( "shoot" ) );
}

void AKartPlayer::MultiShoot_Implementation()
{
	
}


void AKartPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME( AKartPlayer , starCount);

	/*DOREPLIFETIME(AKartPlayer, hasItem);
	DOREPLIFETIME(AKartPlayer, bSpeedUp);*/
}






