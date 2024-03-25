// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "KartGameState.generated.h"

/**
 * 
 */
UCLASS()
class SSACSTARS_API AKartGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UFUNCTION()
	void CountDown();

	UFUNCTION()
	void ReadyTimer();

	UPROPERTY()
	class UCountDownWidget* countDownUI;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UCountDownWidget> CountDownUIFactory;

	UPROPERTY( Replicated )
	int32 min = 1;

	UPROPERTY( Replicated )
	int32 sec = 0;

	UPROPERTY( Replicated )
	int32 num = 4;

	UPROPERTY( EditAnywhere )
	float DelayTime = 1;
};
