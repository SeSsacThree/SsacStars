// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndingWidget.generated.h"

/**
 * 
 */
UCLASS()
class SSACSTARS_API UEndingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UTextBlock* RankingFirst;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UTextBlock* RankingSecond;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UTextBlock* RankingThird;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UTextBlock* RankingFourth;
};
