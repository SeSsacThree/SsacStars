// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PartyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SSACSTARS_API APartyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

	UENUM(BlueprintType)
		enum class EPlayerState : uint8
	{
		WaitTurn	UMETA(DisplayName = "상대턴 대기"),
		StartTurn	UMETA(DisplayName = "내턴시작"),
		SelectBehavior	UMETA(DisplayName = "주사위or아이템or맵"),
		ThrowDice	UMETA(DisplayName = "주사위던지기"),
		Interaction		UMETA(DisplayName = "발판상호작용"),
		PlayAnimation		UMETA(DisplayName = "여러애니메이션 "),
		StartMinigame		UMETA(DisplayName = "미니게임 시작")
	};


	UENUM(BlueprintType)
		enum class ESpaceState : uint8
	{
		Blue	UMETA(DisplayName = "효과없음"),
		Red		UMETA(DisplayName = "코인-3"),
		Item	UMETA(DisplayName = "아이템얻기"),
		Trap	UMETA(DisplayName = "함정발판"),
		Warp		UMETA(DisplayName = "워프발판"),
		Star		UMETA(DisplayName = "별얻기"),
		2SideLoad		UMETA(DisplayName = "갈림길")
	};



};
