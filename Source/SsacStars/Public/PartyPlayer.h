// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlueBoardSpace.h"
#include "PartyGameModeBase.h"
#include "GameFramework/Character.h"
#include "PartyPlayer.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoveCompletedDelegate);

UENUM(BlueprintType)
enum class EItem : uint8
{
	Add3Dice	UMETA(DisplayName = "Add3Dice"),
	WarpToStar	UMETA(DisplayName = "WarpToStar"),
	SwitchCharacter		UMETA(DisplayName = "TwoSideLoad"),
	Nothing	UMETA(DisplayName = "Nothing"),
};



class APartyGameModeBase;

UCLASS()
class SSACSTARS_API APartyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APartyPlayer();


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UWidgetComponent* DiceRemainWidget;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> DiceRemainWidgetFactory;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;








public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MoveRemaining;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Coin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Score = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PlayerIndex;
public:
	bool IsMoving;
	bool IsMovingTurn;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ABlueBoardSpace* CurrentSpace;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APartyGameStateBase* PartyGameState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ARollDiceCharacter* RollDicePlayer;
	UPROPERTY(EditDefaultsOnly)
	class AMap_SpaceFunction* PlayFun;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	class AAIController* Ai;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	APartyGameModeBase* GM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EItem> Inventory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItem ToApplyDo;
	int32 Inventoryindex = 0;
	int32 MaxInventorySize = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Rank = 4;
public:




public:
	UFUNCTION(Server, Reliable)
	void ServerChangeAppereance();
	UFUNCTION(NetMulticast, Reliable)
	void MultiChangeAppereance();
	void GetCamera();
	void SelectBehavior();
	void RollDice();
	void ItemApply();
	void ChooseItem();
	void MoveToSpace(ABlueBoardSpace* currentSpace);
	void MoveEnded();
	void StopOrGo();

	void DelayTime(float WantSeconds, TFunction<void()> InFunction);
	void MyTurnStart();
	void MyTurnEnd();
	void CommandCloseView();


public:



};
