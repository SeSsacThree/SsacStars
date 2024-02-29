// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "PartyGameModeBase.generated.h"

//class UMainUI;
class APartyPlayer;
/**
 * 
 */
UCLASS()
class SSACSTARS_API APartyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;

	/*
	UENUM(BlueprintType)
		enum class EPlayerState : uint8
	{
		WaitTurn	UMETA(DisplayName = "상대턴 대기"),
		StartTurn	UMETA(DisplayName = "내턴시작"),
		SelectBehavior	UMETA(DisplayName = "주사위or아이템or맵"),
		ThrowDice	UMETA(DisplayName = "주사위던지기"),
		Interaction		UMETA(DisplayName = "발판상호작용"),
		PlayAnimation		UMETA(DisplayName = "여러애니메이션 "),
		StartMinigame		UMETA(DisplayName = "미니게임 시작")
	};

	*/

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APartyPlayer*>  TurnOrder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APartyPlayer*>  RoundOrder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APartyPlayer* CurrentPlayer;

	/*
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> PartyUiFactory;
	UPROPERTY()
	class UMainUI* PartyUi;
	*/
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Round;

public:

	void CreateWidget();
	void InitialRound();
	void StartTurn();
	void NextTurn();
	void EndRound();
	void StartMiniGame();
	void AddView();
};
