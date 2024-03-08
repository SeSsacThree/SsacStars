// Fill out your copyright notice in the Description page of Project Settings.


#include "KartPlayer.h"

#include "EngineUtils.h"
#include "ItemBox.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "ItemWidget.h"
#include "MiniGameBullet.h"
#include "MiniGameMainUI.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PrimitiveComponent.h"
#include "TimerManager.h"
#include "Components/ArrowComponent.h"

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
	itemUI = CreateWidget<UItemWidget>(GetWorld(), itemUIFactory);
	itemUI->AddToViewport();
	

	for (TActorIterator<AItemBox> it(GetWorld()); it; ++it)
	{
		AItemBox* box = *it;
		box->itemWidget = itemUI;
	}


	MainUI = CreateWidget<UMiniGameMainUI>(GetWorld(), MainUIFactory);
	MainUI->AddToViewport();
	FTimerHandle Handle;
	
	GetWorldTimerManager().SetTimer(Handle, this, &AKartPlayer::GetReadyTimer, 1.0f, true, 3.0f);
	
	
	
	starCount = 0;

}

// Called every frame
void AKartPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MainUI->SetStarCount();
	//MainUI->CountDown();
	if (bSpeedUp)
	{
		currentTime += GetWorld()->GetDeltaSeconds();

		LaunchCharacter(GetActorForwardVector() * 5000, true, true);

		if (currentTime > speedUpTime)
		{
			speedDown();
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
		AddMovementInput(this->GetActorForwardVector(), Value);
	}
	
}

void AKartPlayer::TurnRight(float Value)
{
	if (!isPaused)
	{
		FRotator NewRotation = this->GetActorRotation();
		NewRotation.Yaw -= Value;
		this->SetActorRotation(NewRotation);
	}
}

void AKartPlayer::useItem()
{
	//플레이어가 아이템이 있을 때만 사용 가능
	if(hasItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("USE ITEM"));
		switch(itemNumber)
		{
		case 1 :
			speedUp();
			//아이템UI 초기화
			itemUI->Init();
			hasItem = false;
			break;
		case 2:
			UE_LOG(LogTemp, Warning, TEXT("use bullet"));
			shoot();
			itemUI->Init();
			hasItem = false;
			break;

		}

	}
	
}

void AKartPlayer::speedUp()
{
	bSpeedUp = true;
	currentTime = 0;
}

void AKartPlayer::speedDown()
{
	bSpeedUp = false;
	//GetCharacterMovement()->Velocity = GetCharacterMovement()->Velocity * 0.5f;
}

void AKartPlayer::starCountUP()
{
	starCount += 1;

}

void AKartPlayer::getSmall()
{
	/*playerMeshComp->SetRelativeScale3D(FVector(0.1f));
	playerMeshComp->SetRelativeLocation(FVector(10.1802, 29.3196, -58.129));
	carMeshComp->SetRelativeScale3D(FVector(40));
	carMeshComp->SetRelativeLocation(FVector(0, 30, -79));

	ct += GetWorld()->GetDeltaSeconds();
	if(ct>dt)
	{
		
	}*/
}

void AKartPlayer::shoot()
{
	
	FTransform t = firePosition->GetComponentTransform();
	GetWorld()->SpawnActor<AMiniGameBullet>(bulletFactory, t);
	UE_LOG(LogTemp, Warning, TEXT("shoot"));
}

void AKartPlayer::GetReadyTimer()
{
	MainUI->GetReadyCount();
}

void AKartPlayer::CountDown()
{
	MainUI->CountDown();
}
