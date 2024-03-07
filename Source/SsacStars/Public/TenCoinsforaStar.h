// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TenCoinsforaStar.generated.h"

/**
 * 
 */
UCLASS()
class SSACSTARS_API UTenCoinsforaStar : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* PassButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UWrapBox* WrapBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* StarImage;

	UPROPERTY(EditAnywhere, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* StarImageAnimation;


	UFUNCTION()
	void ClickedButton();

	UFUNCTION()
	void ClickedPassButton();

	UFUNCTION()
	void GetStarAnimation(UWidgetAnimation* InWidgetAnimation);


	FWidgetAnimationDynamicEvent StarAnimationEvent;

	UFUNCTION()
	void RemoveWidgetAfterAnimation();

};
