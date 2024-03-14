// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PartyScore.h"
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
	APartyGameModeBase();

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
	TArray<class APartyPlayer*>  TurnOrder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APartyPlayer*> InitialTurnOrder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APartyPlayer* CurrentPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APlayerController* PlayerController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APartyScore* Star;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ARollDiceCharacter* RollDiceCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APartyGameStateBase* PartyGameState;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Round;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int>PlayerCoins;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int>PlayerScores;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentPlayerIndex;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMesh* Mesh1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMesh* Mesh2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMesh* Mesh3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMesh* Mesh4;
public:
	void PlayerSetting();
	void SetPlayerAppeareance(APartyPlayer* Player, int Index);
	void SetRollerAppeareance(ARollDiceCharacter* Player, int Index);
	void AddItemUseUi();
	void InitialRound();
	void StartTurn();
	void NextTurn();
	void EndRound();
	void StartMiniGame();
	void AddSelectBehaviorUi();
	void CloseView();
	void ChangeStarSpace();
	void AddTrapUi();
	void AddGetItemUi();
	void AddTenCoinsforaStar();
	void UpdateGameInfo(int Index);
	void UpdateRankInfo();
	UFUNCTION(BlueprintCallable, Category = "Game")
	void GamePause();
	void GameRelease();
};
