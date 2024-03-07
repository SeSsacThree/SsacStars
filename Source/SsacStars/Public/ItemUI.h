// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PartyGameModeBase.h"
#include "PartyPlayer.h"
#include "Blueprint/UserWidget.h"
#include "ItemUI.generated.h"

/**
 * 
 */
UCLASS()
class SSACSTARS_API UItemUI : public UUserWidget
{
	GENERATED_BODY()


	void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Index1Button;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Index2Button;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* A3D1;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* WTS1;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* SC1;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* A3D2;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* WTS2;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* SC2;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* Item1;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* Item2;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	APartyGameModeBase* GM;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UUniformGridPanel* ItemGrid;
	/*
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> Add3DiceUIFactory;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> WarpToStarUIFactory;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> SwitchSpaceUIFactory;
	*/
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UImage> Add3DiceImageFactory;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APartyPlayer* CurrentPlayer;


public:

	void Add3DiceItem(int index);
	void WarpToStarItem(int index);
	void SwitchSpaceItem(int index);
	void RemoveItemUi(int32 index);
	UFUNCTION()
	void Select1Button();
	UFUNCTION()
	void Select2Button();
	void SwitchItem(EItem SelectedItem);

public:
	int32 PlayerItemIndex=0;

	TArray<EItem> PlayerInventory;
	
};