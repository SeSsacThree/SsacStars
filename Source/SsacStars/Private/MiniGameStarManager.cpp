// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGameStarManager.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MiniGameStarPoint.h"
#include "Star.h"
#include "TimerManager.h"
// Sets default values
AMiniGameStarManager::AMiniGameStarManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMiniGameStarManager::BeginPlay()
{
	Super::BeginPlay();
    spawnStar();

}

// Called every frame
void AMiniGameStarManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (bSpawn)
    {
        currentTime += GetWorld()->GetDeltaSeconds();

        if (currentTime > delayTime)
        {
            spawnStar();
            currentTime = 0;
        }
    }

}

void AMiniGameStarManager::spawnStar()
{
    
    TArray<AActor*> starPointArr;
    UWorld* World = GetWorld();
    if (World)
    {
        // starPoint 클래스의 모든 액터를 가져오기
        UGameplayStatics::GetAllActorsOfClass(World, AMiniGameStarPoint::StaticClass(), starPointArr);
        UE_LOG(LogTemp, Warning, TEXT("get all star points"));
        // starPoint 액터 배열이 비어있지 않은 경우에만 랜덤 액터를 선택
        if (starPointArr.Num() > 0)
        {
            // 랜덤하게 starPoint 액터를 선택.
            int32 RandomIndex = FMath::RandRange(0, starPointArr.Num() - 1);
            AActor* SelectedActor = starPointArr[RandomIndex];

            if (SelectedActor)
            {

                // starPoint 액터의 위치값을 가져오기.
                starLocation = SelectedActor->GetActorLocation();
                // star 생성
                World->SpawnActor<AStar>(starFactory, starLocation, FRotator::ZeroRotator);

                bSpawn = false;
            }
        }
    }
}

