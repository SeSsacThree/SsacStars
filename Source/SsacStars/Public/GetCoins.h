// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GetCoins.generated.h"

/**
 *
 */
UCLASS()
class SSACSTARS_API UGetCoins : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image0;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image3;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image4;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image5;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image6;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image7;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image8;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image9;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Image0Animation;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Image1Animation;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Image2Animation;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Image3Animation;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Image4Animation;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Image5Animation;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Image6Animation;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Image7Animation;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Image8Animation;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Image9Animation;

	UPROPERTY(EditAnywhere)
	TArray<class UWidgetAnimation*> AnimationArray;

	UFUNCTION()
	void GetCoins();

	UFUNCTION()
	void DropCoins(UWidgetAnimation* InWidgetAnimation);

	FTimerDelegate TimeDelegate;

	FTimerHandle DelayTimerHandle;

	void DelayTime(float WantSeconds, TFunction<void()> InFunction);

	int DropCoinsNumber;
};
