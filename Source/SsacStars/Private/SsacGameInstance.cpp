// Fill out your copyright notice in the Description page of Project Settings.


#include "SsacGameInstance.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Online/OnlineSessionNames.h"

void USsacGameInstance::Init()
{
	Super::Init();
	//playerScore.SetNum( 4 );
	//playerScore.Init(0,4);

	if (auto subsystem = IOnlineSubsystem::Get())
	{
		sessionInterface = subsystem->GetSessionInterface();

		sessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &USsacGameInstance::OnMyFindOtherRoomsComplete);

		sessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &USsacGameInstance::OnMyFindOtherRoomsComplete);

		sessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &USsacGameInstance::OnMyJoinRoomsComplete);

	}
	//Timer
	/*
	FTimerHandle handle;
	GetTimerManager().SetTimer(handle,[&]()
	{
		// 호출
		FindOtherRooms();
	}, 5, false);*/
}

void USsacGameInstance::CreateRoom(int32 maxplayerCount, FString roomName)
{
	UE_LOG(LogTemp, Warning, TEXT("CreatRoom!!"))

	FOnlineSessionSettings setting;
	
	setting.bIsDedicated = false;
	auto subSys = IOnlineSubsystem::Get();
	setting.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName().IsEqual("Null");
	setting.bShouldAdvertise = true;
	setting.bUsesPresence = true;
	setting.bAllowJoinInProgress = true;
	setting.bAllowJoinViaPresence = true;
	setting.NumPublicConnections = maxplayerCount;
	setting.Set(TEXT("HOST_NAME"), myNickName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	setting.Set(TEXT("ROOM_NAME"), roomName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	FUniqueNetIdPtr netID = GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().GetUniqueNetId();

	UE_LOG(LogTemp, Warning, TEXT("CreateRoom Start!! roomName: %s, netID: %d"), *roomName, *netID->ToString());

	sessionInterface->OnCreateSessionCompleteDelegates.AddUObject( this , &USsacGameInstance::OnMyCreateRoomComplete );
	sessionInterface->CreateSession(*netID, FName(*roomName), setting);

}

void USsacGameInstance::OnMyCreateRoomComplete(FName sessionName, bool bWasSuccessful)
{
	UE_LOG( LogTemp , Warning , TEXT( "CreateRoom Start!! sessionName: %s, bWasSuccessful: %d" ) , *sessionName.ToString() , bWasSuccessful);
	if (bWasSuccessful)
	{
		myRoomName = sessionName.ToString();
		FString url = TEXT("/Game/JYS/Map/WorldMap?listen");
		GetWorld()->ServerTravel(url);
	}
}

void USsacGameInstance::FindOtherRooms()
{
	roomSearch = MakeShareable(new FOnlineSessionSearch);
	roomSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	roomSearch->MaxSearchResults = 10;
	auto subSys = IOnlineSubsystem::Get();
	roomSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName().IsEqual("NULL");

	sessionInterface->FindSessions(0, roomSearch.ToSharedRef());

	if(OnFindingRoomsDelegate.IsBound())
	{
		OnFindingRoomsDelegate.Broadcast(true);
	}
}

void USsacGameInstance::OnMyFindOtherRoomsComplete(bool bWasSuccessful)
{
	if (OnFindingRoomsDelegate.IsBound())
	{
		OnFindingRoomsDelegate.Broadcast( false );
	}
	UE_LOG(LogTemp, Warning, TEXT("%d"), bWasSuccessful)

	for(int i =0; i <roomSearch->SearchResults.Num(); i++)
	{
		auto r = roomSearch->SearchResults[i];
		if (false == r.IsValid())
		continue;

		FRoomInfo info;

		info.index = i;

		r.Session.SessionSettings.Get(TEXT("ROOM_NAME"), info.roomName );

		r.Session.SessionSettings.Get(TEXT("HOST_NAME"), info.hostName);

		int32 max = r.Session.SessionSettings.NumPublicConnections;

		int32 current = max - r.Session.NumOpenPublicConnections;
		info.playerCount = FString::Printf(TEXT("%d/%d"), current, max);

		info.pingMS = FString::Printf(TEXT("%dms"), r.PingInMs);

		info.printLog();

		if (onAddRoomInfoDelegate.IsBound())
		{
			onAddRoomInfoDelegate.Broadcast(info);
		}
	}
}

void USsacGameInstance::JoinRoom(int32 index)
{
	auto r = roomSearch->SearchResults[index];
	FString sessionName;
	r.Session.SessionSettings.Get(TEXT("ROOM_NAME"), sessionName);
	sessionInterface->JoinSession(0,FName(*sessionName),r);
}

void USsacGameInstance::OnMyJoinRoomsComplete(FName sessionName, EOnJoinSessionCompleteResult::Type result )
{
	if (EOnJoinSessionCompleteResult::Success == result)
	{
		myRoomName = sessionName.ToString();
		FString url;
		sessionInterface->GetResolvedConnectString(sessionName, url);

		auto pc = GetWorld()->GetFirstPlayerController();
		pc->ClientTravel(url, TRAVEL_Absolute);
	}else
	{
		UE_LOG(LogTemp,Warning, TEXT("Join Session Faild... : %s, result"));
	}
}


