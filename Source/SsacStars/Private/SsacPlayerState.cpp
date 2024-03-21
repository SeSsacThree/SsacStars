// Fill out your copyright notice in the Description page of Project Settings.


#include "SsacPlayerState.h"

#include "SsacGameInstance.h"

void ASsacPlayerState::BeginPlay()
{
	Super::BeginPlay();

	auto pc = GetPlayerController();
	if (pc && pc->IsLocalController())
	{
		auto gi = GetGameInstance<USsacGameInstance>();
		ServerSetNickName(gi->myNickName);
	}
}

void ASsacPlayerState::ServerSetNickName_Implementation(const FString& newNickName)
{
	SetPlayerName(newNickName);
}
