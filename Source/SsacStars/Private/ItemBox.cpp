// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBox.h"

#include "Components/BoxComponent.h"

// Sets default values
AItemBox::AItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	this->SetRootComponent(boxComp);

	itemBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemBox"));
	itemBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	itemBox->SetupAttachment(RootComponent);;

	boxComp->SetGenerateOverlapEvents(true);
	boxComp->SetCollisionProfileName(TEXT("ItemBox"));
}

// Called when the game starts or when spawned
void AItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

