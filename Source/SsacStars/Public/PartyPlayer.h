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
	int Score;

public:
	bool IsMoving;
	bool IsMovingTurn;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ABlueBoardSpace* CurrentSpace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ARollDiceCharacter* RollDicePlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	class AAIController* Ai;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	APartyGameModeBase* GM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EItem> Inventory;
	int32 Inventoryindex=0;
	int32 MaxInventorySize = 2;

public:




public:

	void GetCamera();
	void SelectBehavior();
	void RollDice();
	void ItemApply();
	void ChooseItem();
	void MoveToSpace(ABlueBoardSpace* currentSpace);
	void MoveEnded();
	void StopOrGo();

	void DelayTime(float WantSeconds, TFunction<void()> InFunction);


	

public:



};
