// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PartyController.generated.h"

/**
 * 
 */



UCLASS()
class SSACSTARS_API APartyController : public APlayerController
{
	GENERATED_BODY()



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ARollDiceCharacter* RollDicePlayer;

public:
	void JumpCharacter();

};
