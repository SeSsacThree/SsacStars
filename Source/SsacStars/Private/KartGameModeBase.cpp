// Fill out your copyright notice in the Description page of Project Settings.


#include "KartGameModeBase.h"

#include "KartPlayer.h"
#include "MiniGameMainUI.h"
#include "Kismet/GameplayStatics.h"

void AKartGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &AKartGameModeBase::CountDown, 1.0f, true, 0.0);
}

void AKartGameModeBase::CountDown()
{
	auto player = Cast<AKartPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AKartPlayer::StaticClass()));
	player->CountDown();
}
