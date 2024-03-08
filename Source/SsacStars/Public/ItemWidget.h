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

	
public:
	bool bSpeedUp = false;
	bool bGetSmall = false;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* ImageItemSpeedUp;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* ImageItemGetSmall;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* ImageQuestion;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* A_Button;

	UFUNCTION()
	void hideQuestion();

	//아이템UI 초기화
	UFUNCTION()
	void Init();

	UFUNCTION()
	void speedUp();

	UFUNCTION()
	void getSmall();

	float currentTime = 0;
	float delayTime = 2.5;
};
