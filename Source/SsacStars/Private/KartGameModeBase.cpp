// Fill out your copyright notice in the Description page of Project Settings.


#include "KartGameModeBase.h"

#include "KartPlayer.h"
#include "MiniGameMainUI.h"
#include "MiniGameStarPoint.h"
#include "Star.h"
#include "Kismet/GameplayStatics.h"

void AKartGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &AKartGameModeBase::CountDown, 1.0f, true, 0.0);
   
}

void AKartGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  
}

void AKartGameModeBase::CountDown()
{
	//MainUI->CountDown();
	//UE_LOG(LogTemp, Warning, TEXT("countdown"));
}
