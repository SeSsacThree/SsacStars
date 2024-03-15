// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGameStarManager.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MiniGameStarPoint.h"
#include "Star.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"
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

	DelaySpawnTimer();
}

void AMiniGameStarManager::DelaySpawnTimer()
{
	//Lambda 함수 구조 [REFERENCE 또는 CAPTURE]()-> Return 타입 {구현부}
	GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, FTimerDelegate::CreateLambda(
		[this]()->void
		{
			ServerSpawnStar();
		}
	), DelayTime, false);
}



void AMiniGameStarManager::ServerSpawnStar_Implementation()
{
	spawnStar();
}



void AMiniGameStarManager::spawnStar()
{
	UWorld* World = GetWorld();
	
	if (starPointArr.Num() == 0)
	{
		// starPoint 클래스의 모든 액터를 가져오기
		UGameplayStatics::GetAllActorsOfClass(World, AMiniGameStarPoint::StaticClass(), starPointArr);
	}

	if (starPointArr.Num() == 0)
	{
		return;
	}

	if (World)
	{
		// starPoint 액터 배열이 비어있지 않은 경우에만 랜덤 액터를 선택
		if (starPointArr.Num() > 0)
		{
			// 랜덤하게 starPoint 액터를 선택.
			const int32 RandomIndex = FMath::RandRange(0, starPointArr.Num() - 1);
			AActor* SelectedActor = starPointArr[RandomIndex];

			if (SelectedActor)
			{
				// starPoint 액터의 위치값을 가져오기.
				const FVector loc = SelectedActor->GetActorLocation();
				// star 생성
				World->SpawnActor<AStar>(starFactory, loc, FRotator::ZeroRotator);

			}
		}
	}
}


void AMiniGameStarManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMiniGameStarManager, starLocation);
}
