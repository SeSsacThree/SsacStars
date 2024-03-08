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
        // starPoint Ŭ������ ��� ���͸� ��������
        UGameplayStatics::GetAllActorsOfClass(World, AMiniGameStarPoint::StaticClass(), starPointArr);
        UE_LOG(LogTemp, Warning, TEXT("get all star points"));
        // starPoint ���� �迭�� ������� ���� ��쿡�� ���� ���͸� ����
        if (starPointArr.Num() > 0)
        {
            // �����ϰ� starPoint ���͸� ����.
            int32 RandomIndex = FMath::RandRange(0, starPointArr.Num() - 1);
            AActor* SelectedActor = starPointArr[RandomIndex];

            if (SelectedActor)
            {

                // starPoint ������ ��ġ���� ��������.
                starLocation = SelectedActor->GetActorLocation();
                // star ����
                World->SpawnActor<AStar>(starFactory, starLocation, FRotator::ZeroRotator);

                bSpawn = false;
            }
        }
    }
}

