// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGameSpeedBoard.h"
#include "KartPlayer.h"
#include "Components/BoxComponent.h"
// Sets default values

AMiniGameSpeedBoard::AMiniGameSpeedBoard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	this->SetRootComponent(boxComp);
	boxComp->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AMiniGameSpeedBoard::BeginPlay()
{
	Super::BeginPlay();
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AMiniGameSpeedBoard::OnMyCompBeginOverlap);
	boxComp->OnComponentEndOverlap.AddDynamic(this, &AMiniGameSpeedBoard::OnMyCompEndOverlap);
}

// Called every frame
void AMiniGameSpeedBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMiniGameSpeedBoard::OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 만약 OtherActor가 플레이어라면
	auto player = Cast<AKartPlayer>(OtherActor);
	if (player)
		player->speedUp();
}

void AMiniGameSpeedBoard::OnMyCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto player = Cast<AKartPlayer>(OtherActor);
	if (player)
		player->speedDown();
}

