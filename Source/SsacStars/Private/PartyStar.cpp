// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyStar.h"
#include "EngineUtils.h"
// Sets default values
APartyStar::APartyStar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void APartyStar::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void APartyStar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

