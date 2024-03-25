// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "SsacGameInstance.generated.h"

USTRUCT()
struct FRoomInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 index;
	UPROPERTY(EditDefaultsOnly)
	FString roomName;
	UPROPERTY( EditDefaultsOnly )
	FString hostName;
	UPROPERTY( EditDefaultsOnly )
	FString playerCount;
	UPROPERTY( EditDefaultsOnly )
	FString pingMS;

	FORCEINLINE void printLog()const
	{
		UE_LOG( LogTemp , Warning , TEXT( "RoomName: %s, HostName: %s, PlayerCount: %s, Ping: %s" ) , *roomName , *hostName , *playerCount , *pingMS );
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAddRoomInfoDelegate, const FRoomInfo&, roomInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFindingRoomsDelegate, bool, bActive);


UCLASS()
class SSACSTARS_API USsacGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	bool IsInRoom();

	UPROPERTY(EditDefaultsOnly)
	TArray<float> playerScore;

	IOnlineSessionPtr sessionInterface;

	FAddRoomInfoDelegate onAddRoomInfoDelegate;

	FFindingRoomsDelegate OnFindingRoomsDelegate;

	FString myNickName = TEXT("Ssac");
	FString myRoomName;

	void CreateRoom(int32 maxplayerCount, FString roomName);

	void OnMyCreateRoomComplete( FName sessionName , bool bWasSuccessful );

	TSharedPtr<FOnlineSessionSearch> roomSearch;

	void FindOtherRooms();

	void OnMyFindOtherRoomsComplete(bool bWasSuccessful);

	void JoinRoom(int32 index);

	void OnMyJoinRoomsComplete(FName sessionName , EOnJoinSessionCompleteResult::Type result);
};


