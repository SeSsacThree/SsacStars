// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MiniGameMainUI.generated.h"

/**
 * 
 */
UCLASS()
class SSACSTARS_API UMiniGameMainUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* StarImage;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* StarCount;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* ReadyCount;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* Minutes;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* Seconds;


	/*UFUNCTION()
	void SetStarCount();*/

	UFUNCTION()
	void GetReadyCount();

	UFUNCTION()
	void HideReady();
	int32 num = 4;

	UFUNCTION()
	void CountDown();

	int32 min = 2;
	int32 sec = 0;
};
