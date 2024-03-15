// Fill out your copyright notice in the Description page of Project Settings.


#include "PinguAnimInstance.h"

#include "PartyPlayer.h"
#include "Kismet/KismetMathLibrary.h"

void UPinguAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	APartyPlayer* player = Cast<APartyPlayer>(TryGetPawnOwner());
	if (nullptr == player)
	{
		return;
	}
	speed = UKismetMathLibrary::VSize(player->GetVelocity());
}
