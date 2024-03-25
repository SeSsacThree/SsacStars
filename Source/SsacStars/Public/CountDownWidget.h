// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CountDownWidget.generated.h"

/**
 * 
 */
UCLASS()
class SSACSTARS_API UCountDownWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UTextBlock* Minutes;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UTextBlock* Seconds;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UTextBlock* ReadyCount;

	UFUNCTION()
	void CountDown(int32 inMin, int32 inSec);

	UFUNCTION()

	void GetReadyCount(int32 inNum);
	UFUNCTION()
	void HideReady();

	int32 min;
	int32 sec;

	
};
