// Fill out your copyright notice in the Description page of Project Settings.


#include "MG_BallFactory.h"

// Sets default values
AMG_BallFactory::AMG_BallFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMG_BallFactory::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMG_BallFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

