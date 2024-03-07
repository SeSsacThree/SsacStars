// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGameItem_SpeedUp.h"

// Sets default values
AMiniGameItem_SpeedUp::AMiniGameItem_SpeedUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMiniGameItem_SpeedUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMiniGameItem_SpeedUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMiniGameItem_SpeedUp::speedUp()
{
}

