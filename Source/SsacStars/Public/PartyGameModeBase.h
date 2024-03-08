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
		WaitTurn	UMETA(DisplayName = "����� ���"),
		StartTurn	UMETA(DisplayName = "���Ͻ���"),
		SelectBehavior	UMETA(DisplayName = "�ֻ���or������or��"),
		ThrowDice	UMETA(DisplayName = "�ֻ���������"),
		Interaction		UMETA(DisplayName = "���ǻ�ȣ�ۿ�"),
		PlayAnimation		UMETA(DisplayName = "�����ִϸ��̼� "),
		StartMinigame		UMETA(DisplayName = "�̴ϰ��� ����")
	};

	*/

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APartyPlayer*>  TurnOrder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APartyPlayer*>  RoundOrder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APartyPlayer* CurrentPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APlayerController* PlayerController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APartyScore* Star;

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UMainUI> SelectUiFactory;
	UPROPERTY()
	class UMainUI* SelectUi;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> StatusUiFactory;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UItemUI> ItemUiFactory;
	UPROPERTY()
	class UItemUI* ItemUi;
	UPROPERTY()
	class UUserWidget* StatusUi;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UTrapWidget> TrapUiFactory;
	UPROPERTY()
	class UTrapWidget* TrapUi;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class URandomItemWidget> GetItemUiFactory;
	UPROPERTY()
	class URandomItemWidget* GetItemUi;
	UPROPERTY()
	class UPlayerUiCard* PlayerUiCard;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UPlayerUiCard> PlayerUiCardFactory;
	UPROPERTY()
	class UTenCoinsforaStar* TenCoinsforaStarUi;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UTenCoinsforaStar> TenCoinsforaStarUiFactory;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Round;


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
	void AddItemUseUi();
	void InitialRound();
	void StartTurn();
	void NextTurn();
	void EndRound();
	void StartMiniGame();void AddSelectBehaviorUi();
	void CloseView();
	void ChangeStarSpace();
	void AddTrapUi();
};
