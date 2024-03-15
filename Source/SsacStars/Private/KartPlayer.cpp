// Fill out your copyright notice in the Description page of Project Settings.


#include "KartPlayer.h"

#include "EngineUtils.h"
#include "ItemBox.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "ItemWidget.h"
#include "KartPlayerController.h"
#include "MiniGameBullet.h"
#include "MiniGameMainUI.h"
#include "Star.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Components/PrimitiveComponent.h"
#include "TimerManager.h"
#include "Components/ArrowComponent.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"
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
	// ��Ʈ�� ���̰�ʹ�.
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

	if (GEngine)
	{
		FString Message = FString::Printf(TEXT("AStar::InitializeWidgets"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);
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
		break;			//���׸� ���켼��
	}

	for (TActorIterator<AStar> it(GetWorld()); it; ++it)
	{
		AStar* star = *it;
		star->mainUI = MainUI;
	}

	//FTimerHandle Handle;
	//GetWorldTimerManager().SetTimer(Handle, this, &AKartPlayer::GetReadyTimer, 1.0f, true, 3.0f);
	//

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
	bSpeedUp = true;
}

//---------------------------------------------------------------------------------------


void AKartPlayer::useItem()
{
	//�÷��̾ �������� ���� ���� ��� ����
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
	bSpeedUp = false;
	//GetCharacterMovement()->Velocity = GetCharacterMovement()->Velocity * 0.5f;
}


//---------------------------------------------------------------------------------------

void AKartPlayer::shoot()
{
	ServerShoot();
	
}

void AKartPlayer::ServerShoot_Implementation()
{
	MultiShoot();
}

void AKartPlayer::MultiShoot_Implementation()
{
	FTransform t = firePosition->GetComponentTransform();
	GetWorld()->SpawnActor<AMiniGameBullet>(bulletFactory, t);
	UE_LOG(LogTemp, Warning, TEXT("shoot"));
}
//---------------------------------------------------------------------------------------
//���� ���� �� ī��Ʈ �ٿ�
//void AKartPlayer::GetReadyTimer()
//{
//	MainUI->GetReadyCount();
//}
//
////Ÿ�̸�
//void AKartPlayer::CountDown()
//{
//	MainUI->CountDown();
//}


//---------------------------------------------------------------------------------------

void AKartPlayer::starCountUP()
{
	starCount ++;
	StarCountText = FText::FromString(FString::FromInt(starCount));
	if(MainUI && MainUI->StarCount)
	{
		MainUI->StarCount->SetText(StarCountText);
	}
}



void AKartPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/*DOREPLIFETIME(AKartPlayer, hasItem);
	DOREPLIFETIME(AKartPlayer, bSpeedUp);*/
}






