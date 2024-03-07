// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyController.h"
#include "RollDiceCharacter.h"

#include "Kismet/GameplayStatics.h"

void APartyController::BeginPlay()
{
	Super::BeginPlay();

	RollDicePlayer = Cast<ARollDiceCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ARollDiceCharacter::StaticClass()));

}



void APartyController::JumpCharacter()
{
	RollDicePlayer->Jump(1000);
}

