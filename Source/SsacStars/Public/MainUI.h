// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"

class APartyGameModeBase;


UCLASS()
class SSACSTARS_API UMainUI : public UUserWidget
{
	GENERATED_BODY()

	void NativeConstruct() override;
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Dice;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Item;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Map;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APartyGameModeBase* GM;

public:
	UFUNCTION()
	void DiceAction();
	UFUNCTION()
	void ItemAction();
	UFUNCTION()
	void MapAction();
};
