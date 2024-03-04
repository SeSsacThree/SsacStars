// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueBoardSpace.h"

// Sets default values
ABlueBoardSpace::ABlueBoardSpace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

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
    UpdateAppearance();
}

void ABlueBoardSpace::UpdateAppearance()
{
    switch (SpaceState)
    {
    case ESpaceState::Blue:
		MeshComponent->SetMaterial(0, BlueMaterial);
        break;
    case ESpaceState::Red:
		MeshComponent->SetMaterial(0, RedMaterial);
        break;
    case ESpaceState::Item:
        MeshComponent->SetMaterial(0, ItemMaterial);
        break;
    case ESpaceState::Trap:
        MeshComponent->SetMaterial(0, TrapMaterial);
        break;
    case ESpaceState::Warp:
        MeshComponent->SetMaterial(0, WarpMaterial);
        break;
    case ESpaceState::Star:
        MeshComponent->SetMaterial(0, StarMaterial);
        break;
    case ESpaceState::TwoSideLoad:
        MeshComponent->SetMaterial(0, BlueMaterial);
        break;
    default:
        break;
    }



}