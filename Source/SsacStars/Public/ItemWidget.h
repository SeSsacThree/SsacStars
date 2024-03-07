// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class SSACSTARS_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* ImageItemSpeedUp;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* ImageItemGetSmall;
public:
	bool bSpeedUp = false;
	bool bGetSmall = false;

	
};
