// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TrapWidget.generated.h"

UCLASS()
class SSACSTARS_API UTrapWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* TrapButtonOne;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* TrapButtonTwo;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* TrapButtonThree;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* FirstTrapButtonAnimation;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* SecondTrapButtonAnimation;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* ThirdTrapButtonAnimation;

	UFUNCTION()
	void BlinkTrapButton(UWidgetAnimation* InWidgetAnimation);

	UFUNCTION()
	void RandomPickTrap();

	UPROPERTY(EditAnywhere)
	TArray<class UWidgetAnimation*> AnimationArray;

	UPROPERTY(EditAnywhere)
	class UWidgetAnimation* RandRange;

	FTimerDelegate TimerDelegate;

	FTimerHandle DelayTimerHandle;

	void DelayTime(float WantSeconds, TFunction<void()> InFunction);

	int RandomNumber;
};
