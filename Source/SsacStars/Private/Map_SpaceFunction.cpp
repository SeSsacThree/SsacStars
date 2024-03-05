// Fill out your copyright notice in the Description page of Project Settings.


#include "Map_SpaceFunction.h"
#include "PartyPlayer.h"
//#include "WBP_RandomItem.h"
#include <random>
#include "PartyGameModeBase.h"
#include "EngineUtils.h"
#include "Misc/OutputDeviceNull.h"
#include "Slate/SGameLayerManager.h"

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
	GM=Cast<APartyGameModeBase>(GetWorld()->GetAuthGameMode());
}


// Called every frame
void AMap_SpaceFunction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}


void AMap_SpaceFunction::TeleportActor(AActor* ActorToTeleport, FVector TeleportDestination)
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

	GM->CurrentPlayer->MoveRemaining+=3;
}

void AMap_SpaceFunction::SwapPlayerPositions(APartyPlayer* CurrentPlayer)
{
	TArray<APartyPlayer*> Players;
	APartyPlayer* myPlayer = nullptr;
	for (TActorIterator<APartyPlayer> It(GetWorld()); It; ++It)
	{
		APartyPlayer* player = *It;
		if (player == CurrentPlayer)
		{
			myPlayer = player;
		}
		else
		{
			Players.Add(player);
		}
	}

	if (!myPlayer)
	{
		return;
	}

	int RandomIndex = FMath::RandRange(0, Players.Num()-1);
	APartyPlayer* OtherPlayer = Players[RandomIndex];

	FVector TempPosition = myPlayer->GetActorLocation();
	myPlayer->SetActorLocation(OtherPlayer->GetActorLocation());
	OtherPlayer->SetActorLocation(TempPosition);
}








