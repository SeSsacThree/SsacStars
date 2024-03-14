// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "SsacGameInstance.generated.h"


/**
 * 
 */
UCLASS()
class SSACSTARS_API USsacGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	IOnlineSessionPtr sessionInterface;

	FString hostName = TEXT("SSac");
	void CreateRoom(int32 maxplayerCount, FString roomName);

	void OnMyCreateRoomComplete( FName sessionName , bool bWasSuccessful );
};
