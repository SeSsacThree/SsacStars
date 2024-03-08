// Fill out your copyright notice in the Description page of Project Settings.

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

public:	
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

	UPROPERTY(EditDefaultsOnly)
	int32 starCount;

	UFUNCTION()
	void useItem();

	UFUNCTION()
	void speedUp();

	UFUNCTION()
	void speedDown();

	UFUNCTION()
	void starCountUP();

	UFUNCTION()
	void getSmall();

	UFUNCTION()
	void shoot();

	bool bSpeedUp=false;
	float currentTime;
	float speedUpTime = 1.5;

	//플레이어가 아이템을 가지고 있는지
	bool hasItem = false;
	//1 : speed Up  2: small size  
	int itemNumber = 0;

	float ct = 0;
	float dt = 6;

	UPROPERTY(EditAnywhere)
	UClass* bulletFactory;

	UFUNCTION()
	void GetReadyTimer();

	UPROPERTY(EditAnywhere)
	bool isPaused=true;

	UFUNCTION()
	void CountDown();
};
