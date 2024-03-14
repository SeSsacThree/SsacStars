// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "StatusUi.generated.h"

class APartyGameModeBase;


UCLASS()
class SSACSTARS_API UStatusUi : public UUserWidget
{
	GENERATED_BODY()


public:


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UPlayerUiCard* PersonalState;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UPlayerUiCard* PersonalState1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UPlayerUiCard* PersonalState2;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UPlayerUiCard* PersonalState3;



};
