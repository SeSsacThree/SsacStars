// Fill out your copyright notice in the Description page of Project Settings.


#include "KartPlayerState.h"
#include "Net/UnrealNetwork.h"


void AKartPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//DOREPLIFETIME( AKartPlayerState ,Score );
}
