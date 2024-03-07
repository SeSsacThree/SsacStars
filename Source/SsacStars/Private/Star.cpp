// Fill out your copyright notice in the Description page of Project Settings.


#include "Star.h"
#include "MiniGameStarManager.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include <KartPlayer.h>

#include "Kismet/GameplayStatics.h"
#include <GameFramework/RotatingMovementComponent.h>

// Sets default values
AStar::AStar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("boxComp"));
	this->SetRootComponent(sphereComp);
	sphereComp->SetGenerateOverlapEvents(true);
	sphereComp->SetCollisionProfileName(TEXT("Star"));


	star = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Star"));
	star->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	star->SetupAttachment(RootComponent);;

	Movement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Movement"));
}

// Called when the game starts or when spawned
void AStar::BeginPlay()
{
	Super::BeginPlay();
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AStar::OnMyCompBeginOverlap);
}

// Called every frame
void AStar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Movement->RotationRate = FRotator(0.0f, rotateSpeed, 0.0f);
}

void AStar::OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 만약 OtherActor가 플레이어라면
	if (OtherActor->IsA<AKartPlayer>())
	{
		auto player = Cast<AKartPlayer>(OtherActor);
		player->starCountUP();
		this->Destroy();

		auto manager = Cast<AMiniGameStarManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AMiniGameStarManager::StaticClass()));
		manager->bSpawn=true;
	}
}

