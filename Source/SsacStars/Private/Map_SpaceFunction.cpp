// Fill out your copyright notice in the Description page of Project Settings.


#include "Map_SpaceFunction.h"
#include "PartyPlayer.h"
//#include "WBP_RandomItem.h"
#include "Misc/OutputDeviceNull.h"

// Sets default values
AMap_SpaceFunction::AMap_SpaceFunction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
// Called when the game starts or when spawned
void AMap_SpaceFunction::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AMap_SpaceFunction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AMap_SpaceFunction::TeleportActor(AActor* ActorToTeleport)
{
	if (ActorToTeleport && ActorToTeleport->IsValidLowLevel())
	{
		ActorToTeleport->SetActorLocation(TeleportDestination);
	}
}

void AMap_SpaceFunction::PlusThreeSpaces()
{
	APartyPlayer PartyPlayerInstance;
	PartyPlayerInstance.MoveRemaining +=3;
	PartyPlayerInstance.StopOrGo();
}
/*
TArray<APartyGameModeBase*> Players;
void AMap_SpaceFunction::SwapPlayerPositions(APartyGameModeBase* CurrentPlayer)
{
	APartyGameModeBase* myPlayer = nullptr;
	for (APartyGameModeBase* Player : Players)
	{
		if (Player->PlayerController() == CurrentPlayer)
		{
			myPlayer = Player;
			break;
		}
	}

	if (!myPlayer)
	{
		
	}
}*/








