// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MiniGameStarManager.generated.h"

UCLASS()
class SSACSTARS_API AMiniGameStarManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMiniGameStarManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(Replicated)
	FVector starLocation;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AStar> starFactory;

	void spawnStar();

	void DelaySpawnTimer();

	FTimerHandle DelayTimerHandle;
	//2√  Delay
	UPROPERTY(EditAnywhere)
	float DelayTime = 2;
	//Looping ø©∫Œ
	UPROPERTY(EditAnywhere)
	bool bIsLoop = false;

	//----------------------
	UFUNCTION(Server,Reliable)
	void ServerSpawnStar();

	UPROPERTY()
	TArray<AActor*> starPointArr;


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
