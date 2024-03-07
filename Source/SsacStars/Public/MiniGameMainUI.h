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

	UFUNCTION()
	void SetStarCount();



};
