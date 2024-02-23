// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueBoardSpace.h"

// Sets default values
ABlueBoardSpace::ABlueBoardSpace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABlueBoardSpace::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlueBoardSpace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

