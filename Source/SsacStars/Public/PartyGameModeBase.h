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
		WaitTurn	UMETA(DisplayName = "����� ���"),
		StartTurn	UMETA(DisplayName = "���Ͻ���"),
		SelectBehavior	UMETA(DisplayName = "�ֻ���or������or��"),
		ThrowDice	UMETA(DisplayName = "�ֻ���������"),
		Interaction		UMETA(DisplayName = "���ǻ�ȣ�ۿ�"),
		PlayAnimation		UMETA(DisplayName = "�����ִϸ��̼� "),
		StartMinigame		UMETA(DisplayName = "�̴ϰ��� ����")
	};


	UENUM(BlueprintType)
		enum class ESpaceState : uint8
	{
		Blue	UMETA(DisplayName = "ȿ������"),
		Red		UMETA(DisplayName = "����-3"),
		Item	UMETA(DisplayName = "�����۾��"),
		Trap	UMETA(DisplayName = "��������"),
		Warp		UMETA(DisplayName = "��������"),
		Star		UMETA(DisplayName = "�����"),
		2SideLoad		UMETA(DisplayName = "������")
	};



};
