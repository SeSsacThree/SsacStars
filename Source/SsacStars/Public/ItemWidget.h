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

public:

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

	//������UI �ʱ�ȭ
	UFUNCTION()
	void Init();

	UFUNCTION()
	void speedUp();

	UFUNCTION()
	void shooting();


	FTimerHandle DelayTimerHandle;
	//2�� Delay
	UPROPERTY(EditAnywhere)
	float DelayTime = 2;
	//Looping ����
	UPROPERTY(EditAnywhere)
	bool bIsLoop = false;


};
