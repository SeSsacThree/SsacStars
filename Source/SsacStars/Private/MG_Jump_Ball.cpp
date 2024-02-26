// Fill out your copyright notice in the Description page of Project Settings.


#include "MG_Jump_Ball.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMG_Jump_Ball::AMG_Jump_Ball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);

	boxComp->SetWorldScale3D(FVector(3.0f));
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(boxComp);


	SetActorLocation(FVector(0));
}

// Called when the game starts or when spawned
void AMG_Jump_Ball::BeginPlay()
{
	Super::BeginPlay();
	dir = GetActorRightVector();

	
}

// Called every frame
void AMG_Jump_Ball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	int32 drawResult = FMath::RandRange(0,9);

	if (drawResult < 4)
	{
		MoveBallRight();
	} else
	{
		MoveBallLeft();
	}
}

void AMG_Jump_Ball::MoveBallRight()
{
	FVector NewLocation = dir * moveSpeed * GetWorld()->GetDeltaSeconds();
	SetActorLocation(GetActorLocation() + NewLocation);
}

void AMG_Jump_Ball::MoveBallLeft()
{
	FVector NewLocation = -dir * moveSpeed * GetWorld()->GetDeltaSeconds();
	SetActorLocation(GetActorLocation() + NewLocation);
}

