// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PartyGameModeBase.h"
#include "GameFramework/Character.h"
#include "Dice.generated.h"

UCLASS()
class SSACSTARS_API ADice : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADice();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnDicePoint1BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnDicePoint2BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnDicePoint3BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnDicePoint4BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnDicePoint5BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnDicePoint6BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	void ThrowDice();
	void StartDiceRolling();
	void AfterOverlap();
	void LaunchDice(float LaunchAmount);
public:
	bool IsRollingMode=false;
	bool IsStopRollingMode = false;
public:
	FVector RollingLocation;
	FVector StopRollingLocation;

public:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* DicePoint1;
	UPROPERTY(EditAnywhere)
	class UBoxComponent* DicePoint2;
	UPROPERTY(EditAnywhere)
	class UBoxComponent* DicePoint3;
	UPROPERTY(EditAnywhere)
	class UBoxComponent* DicePoint4;
	UPROPERTY(EditAnywhere)
	class UBoxComponent* DicePoint5;
	UPROPERTY(EditAnywhere)
	class UBoxComponent* DicePoint6;
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* DiceMesh;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	APartyGameModeBase* GM;
};
