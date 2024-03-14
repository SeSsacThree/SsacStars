// Fill out your copyright notice in the Description page of Project Settings.


#include "SsacGameInstance.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"

void USsacGameInstance::Init()
{
	Super::Init();

	if (auto subsystem = IOnlineSubsystem::Get())
	{
		sessionInterface = subsystem->GetSessionInterface();
	}
	//TimerS
	//FTimerHandle handle;
	//GetTimerManager().SetTimer(handle,[&]()
	//{
	//	// 호출
	//}, 5, false);
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
	setting.Set(TEXT("HOST_NAME"), hostName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	setting.Set(TEXT("ROOM_NAME"), roomName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	FUniqueNetIdPtr netID = GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().GetUniqueNetId();

	UE_LOG(LogTemp, Warning, TEXT("CreateRoom Start!! roomName: %s, netID: %d"), *roomName, *netID->ToString());

	sessionInterface->OnCreateSessionCompleteDelegates.AddUObject( this , &USsacGameInstance::OnMyCreateRoomComplete );
	sessionInterface->CreateSession(*netID, FName(*roomName), setting);

}

void USsacGameInstance::OnMyCreateRoomComplete(FName sessionName, bool bWasSuccessful)
{
	UE_LOG( LogTemp , Warning , TEXT( "CreateRoom Start!! sessionName: %s, bWasSuccessful: %d" ) , *sessionName.ToString() , bWasSuccessful);
}
