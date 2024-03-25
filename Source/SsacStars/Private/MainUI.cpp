// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"
#include "PartyGameModeBase.h"
#include "PartyGameStateBase.h"
#include "PartyPlayer.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Microsoft/AllowMicrosoftPlatformTypes.h"
#include "Net/UnrealNetwork.h"

void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();
	Dice->OnClicked.AddDynamic(this, &UMainUI::DiceAction);
	Item->OnClicked.AddDynamic(this, &UMainUI::ItemAction);
	Map->OnClicked.AddDynamic(this, &UMainUI::MapAction);
	PartyGameState = Cast<APartyGameStateBase>(GetWorld()->GetGameState());
	GM = Cast<APartyGameModeBase>(GetWorld()->GetAuthGameMode());
	Dice->SetVisibility(ESlateVisibility::Visible);
	
}

void UMainUI::DiceAction()
{
	/*
	if(PartyGameState->CurrentPlayer)
	{
		PartyGameState->CurrentPlayer->RollDice();

		
	}
	else
	{
		GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Red , TEXT( "RollDIceNo" ) );
		return;
		
	}
	*/
	
	//PartyGameState->ServerRollDice();
	//PartyGameState->ServerRollDice();
	PartyGameState->CurrentPlayer->RollDice();
		
		//PartyGameState->ServerRollDice();

}

void UMainUI::ItemAction()
{
	PartyGameState->CurrentPlayer->ChooseItem();
	//GM->CurrentPlayer->ChooseItem();
}

void UMainUI::MapAction()
{
}



void UMainUI::ServerDiceAction_Implementation()
{
	MultiDiceAction();
}

void UMainUI::MultiDiceAction_Implementation()
{
	PartyGameState->ServerRollDice();
}
void UMainUI::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

}