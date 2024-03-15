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
	//Lambda �Լ� ���� [REFERENCE �Ǵ� CAPTURE]()-> Return Ÿ�� {������}
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
		// starPoint Ŭ������ ��� ���͸� ��������
		UGameplayStatics::GetAllActorsOfClass(World, AMiniGameStarPoint::StaticClass(), starPointArr);
	}

	if (starPointArr.Num() == 0)
	{
		return;
	}

	if (World)
	{
		// starPoint ���� �迭�� ������� ���� ��쿡�� ���� ���͸� ����
		if (starPointArr.Num() > 0)
		{
			// �����ϰ� starPoint ���͸� ����.
			const int32 RandomIndex = FMath::RandRange(0, starPointArr.Num() - 1);
			AActor* SelectedActor = starPointArr[RandomIndex];

			if (SelectedActor)
			{
				// starPoint ������ ��ġ���� ��������.
				const FVector loc = SelectedActor->GetActorLocation();
				// star ����
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
