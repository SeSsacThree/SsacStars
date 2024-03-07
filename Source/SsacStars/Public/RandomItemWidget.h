// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RandomItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class SSACSTARS_API URandomItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ButtonOne;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ButtonTwo;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ButtonThree;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* ButtonOneBlinkAnimation;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* ButtonTwoBlinkAnimation;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* ButtonThreeBlinkAnimation;

	UFUNCTION()
	void BlinkButton(UWidgetAnimation* InWidgetAnimation);

	UFUNCTION()
	void RandomPickItem();

	UPROPERTY(EditAnywhere)
	TArray<class UWidgetAnimation*> AnimationArray;

	UPROPERTY(EditAnywhere)
	class UWidgetAnimation* RandRange;

	/*UPROPERTY()            
	UWidgetAnimation* OutWidgetAnimation;*/

	FTimerDelegate TimerDelegate;

	FTimerHandle DelayTimerHandle;

	void DelayTime(float WantSeconds, TFunction<void()> InFunction);

	int RandomNumber;

	int32 ArrayIndex;

	UPROPERTY(EditDefaultsOnly)
	class AMap_SpaceFunction* oneOfRandomItems;

	UPROPERTY()
	class APartyGameModeBase* GM;

	void ApplyTrap(int32 InArrayNumber);


	FWidgetAnimationDynamicEvent StarAnimationEvent;

	/*
	UPROPERTY()
	class UTenCoinsforaStar* removeWidget;*/

	UFUNCTION()
	void RemoveWidgetAfterAnimation();

};
