// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MinimapWidget.generated.h"

/**
 * 
 */
UCLASS()
class SSACSTARS_API UMinimapWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeTick( const FGeometry& MyGeometry , float InDeltaTime ) override;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UTextBlock* RankingFirst;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UTextBlock* RankingSecond;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UTextBlock* RankingThird;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UTextBlock* RankingFourth;

	
};
