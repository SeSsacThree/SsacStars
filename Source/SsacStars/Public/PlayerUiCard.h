// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUiCard.generated.h"

/**
 * 
 */
UCLASS()
class SSACSTARS_API UPlayerUiCard : public UUserWidget
{
	GENERATED_BODY()

	void NativeConstruct() override;
	
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	class APartyPlayer* CurrentPlayer;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class APartyGameModeBase* GM;

public:
	UPROPERTY(EditDefaultsOnly)
	class UImage* Profile;
	UPROPERTY(EditDefaultsOnly)
	class UImage* Star;
	UPROPERTY(EditDefaultsOnly)
	class UImage* Coin;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* StarScore;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* CoinScore;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* MainScore;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TurnOrderScore;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UBorder* SpaceType;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TurnIndex;


public:
	void SetStarScoreText(int32 score);
	void SetCoinScoreText(int32 score);
	void SetMainScoreText(int32 score);
	void SetTurnOrderScoreText(int32 Score);
	void SetSpaceTypeBorder(APartyPlayer* Player);


};
