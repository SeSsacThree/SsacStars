// Fill out your copyright notice in the Description page of Project Settings.


#include "KartPlayer.h"
#include "Camera/CameraComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"

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
}

// Called when the game starts or when spawned
void AKartPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKartPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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