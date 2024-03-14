// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dice.generated.h"

UCLASS()
class SSACSTARS_API ADice : public AActor
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
	void SetRotationToNumber(int Number);
	void ReBack();

public:
	UFUNCTION(Server, Reliable)
	void ServerThrowDice();
	UFUNCTION(NetMulticast, Reliable)
	void MultiThrowDice();
	UFUNCTION(Server, Reliable)
	void ServerStartDiceRolling();
	UFUNCTION(NetMulticast, Reliable)
	void MultiStartDiceRolling();
	UFUNCTION(Server, Reliable)
	void ServerAfterOverlap();
	UFUNCTION(NetMulticast, Reliable)
	void MultiAfterOverlap();
public:
	bool IsRollingMode = false;
	bool IsStopRollingMode = false;
	bool IsUpMode = false;
	bool IsSelected = false;
public:
	FVector BeginLocation;
	FVector RollingLocation;
	FVector StopRollingLocation;
public:
	int DiceNumber;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneCaptureComponent2D* SceneCaptureDice;
	UPROPERTY(EditAnywhere, Replicated)
	class USkeletalMeshComponent* DiceComp;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	class APartyGameModeBase* GM;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APartyGameStateBase* PartyGameState;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
