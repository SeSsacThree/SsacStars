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
public:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Index1Button;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Index2Button;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), BlueprintReadWrite)
	class UImage* A3D1;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), BlueprintReadWrite)
	class UImage* WTS1;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), BlueprintReadWrite)
	class UImage* SC1;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), BlueprintReadWrite)
	class UImage* A3D2;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), BlueprintReadWrite)
	class UImage* WTS2;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), BlueprintReadWrite)
	class UImage* SC2;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* Item1;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* Item2;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	APartyGameModeBase* GM;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APartyGameStateBase* PartyGameState;
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

	void Add3DiceItem();
	void WarpToStarItem();
	void SwitchSpaceItem();
	void RemoveItemUi(int32 index);
	void Select1Button();
	void Select2Button();
	void SwitchItem(EItem SelectedItem);

public:
	int32 PlayerItemIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	TArray<EItem> PlayerInventory;
	TArray<EItem> ButtonStaus;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};