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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APartyGameStateBase* PartyGameState;


public:
	UFUNCTION()
	void ClickedButton();

	UFUNCTION()
	void ClickedPassButton();

	UFUNCTION()
	void GetStarAnimation(UWidgetAnimation* InWidgetAnimation);


	FWidgetAnimationDynamicEvent StarAnimationEvent;

	UFUNCTION()
	void RemoveWidgetAfterAnimation();


	UFUNCTION(Server, Reliable)
	void ServerClickedButton();
	UFUNCTION(NetMulticast, Reliable)
	void MultiClickedButton();
	UFUNCTION(Server, Reliable)
	void ServerRemoveWidgetAfterAnimation();
	UFUNCTION(NetMulticast, Reliable)
	void MultiRemoveWidgetAfterAnimation();
	UFUNCTION(Server, Reliable)
	void ServerGetStarAnimation(UWidgetAnimation* InWidgetAnimation);
	UFUNCTION(NetMulticast, Reliable)
	void MultiGetStarAnimation(UWidgetAnimation* InWidgetAnimation);
	void DelayTime( float WantSeconds , TFunction<void()> InFunction );

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


};
