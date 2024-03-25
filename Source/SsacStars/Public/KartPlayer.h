﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KartPlayer.generated.h"

UCLASS()
class SSACSTARS_API AKartPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKartPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	virtual void PossessedBy(AController* NewController) override;
public:

	void InitializeWidgets();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float Value);
	void TurnRight(float Value);

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* playerMeshComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* carMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* springArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* cameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* firePosition;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UItemWidget> itemUIFactory;

	UPROPERTY()
	class UItemWidget* itemUI;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UMiniGameMainUI> MainUIFactory;

	UPROPERTY()
	class UMiniGameMainUI* MainUI;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UEndingWidget> EndingUIFactory;

	UPROPERTY()
	UEndingWidget* EndingUI;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool isEnd = false;

	

	UPROPERTY(ReplicatedUsing = OnRep_UpdateStarCountUI, EditDefaultsOnly)
	int32 starCount = 0;

	FText StarCountText;

	UFUNCTION()
	void OnRep_UpdateStarCountUI();

	UFUNCTION(Server, Reliable)
	void ServerSetStarCount( int32 InStarCount );

	UFUNCTION()
	void useItem();

	UFUNCTION()
	void Boost();

	UFUNCTION()
	void speedUp();

	UFUNCTION()
	void speedDown();


	UFUNCTION()
	void shoot();

	UPROPERTY()
	bool bSpeedUp=false;

	float currentTime;
	float speedUpTime = 2;

	//플레이어가 아이템을 가지고 있는지
	UPROPERTY()
	bool hasItem = false;
	//1 : speed Up  2: small size  
	int itemNumber = 0;

	UPROPERTY( EditAnywhere )
	class USoundBase* speedSound;
	UPROPERTY( EditAnywhere )
	class USoundBase* shootingSound;

	UPROPERTY(EditAnywhere)
	UClass* bulletFactory;

	UPROPERTY(EditAnywhere)
	bool isPaused=true;

	

	// Network ---------------------------------------------------------------
	UFUNCTION(Server, Reliable)
	void ServerMoveForward(float Value);

	UFUNCTION(NetMulticast, Reliable)
	void MultiMoveForward(float Value);

	UFUNCTION(Server, Reliable)
	void ServerTurnRight(float Value);

	UFUNCTION(NetMulticast, Reliable)
	void MultiTurnRight(float Value);

	UFUNCTION(Server, Reliable)
	void ServeUseItem();

	UFUNCTION(NetMulticast, Reliable)
	void MultiUseItem();

	UFUNCTION( Server , Reliable )
	void ServerBoost();

	UFUNCTION( NetMulticast , Reliable )
	void MultiBoost();

	UFUNCTION(Server, Reliable)
	void ServerSpeedUp();

	UFUNCTION(NetMulticast, Reliable)
	void MultiSpeedUp();

	UFUNCTION( Server , Reliable )
	void ServerSpeedDown();

	UFUNCTION( NetMulticast , Reliable )
	void MultiSpeedDown();

	UFUNCTION(Server, Reliable)
	void ServerShoot();

	UFUNCTION(NetMulticast, Reliable)
	void MultiShoot();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
