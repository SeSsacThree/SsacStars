// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KartGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SSACSTARS_API AKartGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void CountDown();

	UPROPERTY(EditAnywhere)
	float currentTime = 0;

	UPROPERTY(EditAnywhere)
	float delayTime = 2.0f;
};
