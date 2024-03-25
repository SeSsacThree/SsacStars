// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SsacPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SSACSTARS_API ASsacPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable)
	void ServerSetNickName(const FString& newNickName);
};
