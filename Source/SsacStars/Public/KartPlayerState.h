﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "KartPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SSACSTARS_API AKartPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;


};
