// Fill out your copyright notice in the Description page of Project Settings.


#include "Map_SpaceFunction.h"
//#include "WBP_RandomItem.h"
#include "Misc/OutputDeviceNull.h"
#include "C:\Program Files\Epic Games\UE_5.3\Engine\Source\Runtime\UMG\Public\Blueprint\UserWidget.h"
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

//UWBP_RandomItem* RandomItemWidget = Cast<UWBP_RandomItem>(ItemWidgetClass->GetDefaultObject());
//if (RandomItemWidget)
//{
	//RandomItemWidget->AddToViewport();
//}
	//ItemNames.Add(TEXT("첫번째 아이템"));
	//ItemNames.Add(TEXT("두번째 아이템"));
	//ItemNames.Add(TEXT("세번째 아이템"));

	// StartItemSimulation();
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








