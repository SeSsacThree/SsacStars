// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PartyGameEnd.generated.h"

/**
 * 
 */
UCLASS()
class SSACSTARS_API UPartyGameEnd : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY( EditDefaultsOnly , meta = (BindWidgetAnim) , Transient )
	class UWidgetAnimation* PartyGameEnd; // 애니메이션
	UPROPERTY( EditDefaultsOnly , meta = (BindWidgetAnim) , Transient )
	class UWidgetAnimation* Score;
};
