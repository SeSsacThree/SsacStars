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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector starLocation;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AStar> starFactory;

	void spawnStar();

	UPROPERTY(EditAnywhere)
	bool bSpawn = false;

	UPROPERTY(EditAnywhere)
	float currentTime = 0;

	UPROPERTY(EditAnywhere)
	float delayTime = 2.0f;
};
