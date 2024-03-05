// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RollDiceCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SSACSTARS_API ARollDiceCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;




public:
	// Sets default values for this character's properties
	ARollDiceCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	UPROPERTY(VisibleAnywhere)
	USceneCaptureComponent2D* SceneCaptureComponent;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pistol)
	class USceneComponent* handComp;
	//UPROPERTY()
	//class AActor* Dice;

	UPROPERTY()
	class ADice* Dice;

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UThrowDiceCharacterUi> ThrowDiceUiFactory;
	UPROPERTY()
	class UThrowDiceCharacterUi* ThrowDiceUi;


	void CreateDice();
	void ThrowDice(const AActor* Actor);
	void GrapDice(const AActor* Actor);
	void GetSignal();
	void StartRolling();
	void AddView();
	void CloseView();
	void Jump(float LaunchAmount);


};
