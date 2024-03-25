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
	UFUNCTION()
	void ThrowDice();
	UFUNCTION()
	void StartDiceRolling();
	UFUNCTION(BlueprintCallable)
	void AfterOverlap();
	UFUNCTION()
	void LaunchDice(float LaunchAmount);
	UFUNCTION()
	void SetRotationToNumber(int Number);
	UFUNCTION()
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
	UFUNCTION( Server , Reliable )
	void ServerSetting();

public:
	UPROPERTY( EditAnywhere , Replicated )
	bool IsRollingMode = false;
	UPROPERTY( EditAnywhere , Replicated )
	bool IsStopRollingMode = false;
	UPROPERTY( EditAnywhere , Replicated )
	bool IsUpMode = false;
	UPROPERTY( EditAnywhere )
	bool IsSelected = false;
public:
	UPROPERTY( EditAnywhere , Replicated )
	FTransform BeginTransform;
	UPROPERTY( EditAnywhere , Replicated )
	FVector BeginLocation;
	UPROPERTY( EditAnywhere , Replicated )
	FVector RollingLocation;
	UPROPERTY( EditAnywhere , Replicated )
	FVector StopRollingLocation;
public:
	UPROPERTY( EditAnywhere , Replicated )
	int DiceNumber;

public:

	UPROPERTY(EditAnywhere )
	class UBoxComponent* DicePoint1;
	UPROPERTY(EditAnywhere  )
	class UBoxComponent* DicePoint2;
	UPROPERTY(EditAnywhere )
	class UBoxComponent* DicePoint3;
	UPROPERTY(EditAnywhere )
	class UBoxComponent* DicePoint4;
	UPROPERTY(EditAnywhere )
	class UBoxComponent* DicePoint5;
	UPROPERTY(EditAnywhere )
	class UBoxComponent* DicePoint6;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USceneCaptureComponent2D* SceneCaptureDice;
	UPROPERTY(EditAnywhere,Replicated)
	class USkeletalMeshComponent* DiceComp;



public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	class APartyGameModeBase* GM;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APartyGameStateBase* PartyGameState;
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	class ARollDiceCharacter* RollDiceCharacter;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
