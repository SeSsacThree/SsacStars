// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "RollDiceCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SSACSTARS_API ARollDiceCharacter : public AActor
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
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	UPROPERTY(VisibleAnywhere , Replicated )
	class USceneCaptureComponent2D* SceneCaptureComponent;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dice,Replicated)
	class USceneComponent* handComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* MeshComp;
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	class APartyGameStateBase* PartyGameState;
	//UPROPERTY()
	//class AActor* Dice;

	UPROPERTY(EditDefaultsOnly, Replicated)
	class ADice* Dice;
public:


public:
	FVector BeginLocation;
public:
	/*
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UThrowDiceCharacterUi> ThrowDiceUiFactory;
	//UPROPERTY(Replicated)
	class UThrowDiceCharacterUi* ThrowDiceUi;
	*/
	UFUNCTION()
	void CreateDice();
	UFUNCTION()
	void ThrowDice(const AActor* Actor);
	UFUNCTION()
	void GrapDice(const AActor* Actor);
	UFUNCTION()
	void GetSignal();
	UFUNCTION()
	void StartRolling();
	UFUNCTION()
	void AddView();
	UFUNCTION()
	void CloseView();
	UFUNCTION()
	void Jump(float LaunchAmount);
	void DelayTime(float WantSeconds, TFunction<void()> InFunction);


public:
	UFUNCTION(Server, Reliable)
	void ServerViewThrowDiceUi();
	UFUNCTION(NetMulticast, Reliable)
	void MultiViewThrowDiceUi();
	UFUNCTION(Server, Reliable)
	void ServerRemoveThrowDiceUi();
	UFUNCTION(NetMulticast, Reliable)
	void MultiRemoveThrowDiceUi();


public:
	UFUNCTION(Server, Reliable)
	void ServerGrabDice(const AActor* Actor);
	UFUNCTION(NetMulticast, Reliable)
	void MultiGrabDice(const AActor* Actor);
	UFUNCTION(Server, Reliable)
	void ServerThrowDice(const AActor* Actor);
	UFUNCTION(NetMulticast, Reliable)
	void MultiThrowDice(const AActor* Actor);
	UFUNCTION(Server, Reliable)
	void ServerCreateDice();
	UFUNCTION(NetMulticast, Reliable)
	void MultiCreateDice();



public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
