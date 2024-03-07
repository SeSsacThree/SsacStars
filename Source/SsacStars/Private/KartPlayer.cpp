// Fill out your copyright notice in the Description page of Project Settings.


#include "KartPlayer.h"

#include "EngineUtils.h"
#include "ItemBox.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "ItemWidget.h"
#include "MiniGameMainUI.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PrimitiveComponent.h"
#include "TimerManager.h"

// Sets default values
AKartPlayer::AKartPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetWorldLocation(FVector(0, -800, 577));
	springArmComp->SetWorldRotation(FRotator(-12, 90, 0));
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraComp"));
	cameraComp->SetupAttachment(springArmComp);

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
}

void AKartPlayer::MoveForward(float Value)
{
	AddMovementInput(this->GetActorForwardVector(), Value);	
}

void AKartPlayer::TurnRight(float Value)
{
	FRotator NewRotation = this->GetActorRotation();
	NewRotation.Yaw -= Value;
	this->SetActorRotation(NewRotation);
	
}

void AKartPlayer::speedUp()
{
	bSpeedUp = true;
	currentTime = 0;
	UE_LOG(LogTemp, Warning, TEXT("speed up"));

}

void AKartPlayer::speedDown()
{
	UE_LOG(LogTemp, Warning, TEXT("speed down"));
	bSpeedUp = false;
	//GetCharacterMovement()->Velocity = GetCharacterMovement()->Velocity * 0.5f;

}

void AKartPlayer::starCountUP()
{
	starCount += 1;

}
