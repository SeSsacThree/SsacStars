// Fill out your copyright notice in the Description page of Project Settings.


#include "Star.h"
#include "MiniGameStarManager.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include <KartPlayer.h>

#include "Kismet/GameplayStatics.h"
#include <GameFramework/RotatingMovementComponent.h>

#include "KartGameModeBase.h"
#include "MiniGameMainUI.h"
#include "Components/TextBlock.h"

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

	if (AKartPlayer* OverlapPlayer = Cast<AKartPlayer>(OtherActor)) {
		if (!OverlapPlayer->GetController()) { return; }

		if (OverlapPlayer->GetController()->IsLocalPlayerController()) {

			UGameplayStatics::PlaySound2D( GetWorld() , starSound );
			OverlapPlayer->ServerSetStarCount( 1 );
		}
		// 서버 RPC로 서버에 요청하고
		ServerDestroy();
	}
}


void AStar::ServerDestroy_Implementation()
{
	auto manager = Cast<AMiniGameStarManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AMiniGameStarManager::StaticClass()));
	if (manager)
	{
		manager->DelaySpawnTimer();
	}
	this->Destroy();
}



