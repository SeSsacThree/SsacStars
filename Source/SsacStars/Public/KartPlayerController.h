// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KartPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SSACSTARS_API AKartPlayerController : public APlayerController
{
	GENERATED_BODY()

public:


	UPROPERTY()
	class UItemWidget* itemUI;

	UPROPERTY()
	class UMiniGameMainUI* MainUI;

	
};
