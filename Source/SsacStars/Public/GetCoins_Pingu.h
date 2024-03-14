// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GetCoins_Pingu.generated.h"

/**
 *
 */
UCLASS()
class SSACSTARS_API UGetCoins_Pingu : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image_Pingu0;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image_Pingu1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image_Pingu2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image_Pingu3;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image_Pingu4;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image_Pingu5;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image_Pingu6;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image_Pingu7;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image_Pingu8;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image_Pingu9;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Image_PinguAnimation0;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Image_PinguAnimation1;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Image_PinguAnimation2;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Image_PinguAnimation3;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Image_PinguAnimation4;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Image_PinguAnimation5;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Image_PinguAnimation6;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Image_PinguAnimation7;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Image_PinguAnimation8;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Image_PinguAnimation9;

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
