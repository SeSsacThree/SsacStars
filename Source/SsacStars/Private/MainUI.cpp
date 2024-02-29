// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"

#include "PartyGameModeBase.h"
#include "PartyPlayer.h"
#include "Components/Button.h"

void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();
	Dice->OnClicked.AddDynamic(this, &UMainUI::DiceAction);
	Item->OnClicked.AddDynamic(this, &UMainUI::ItemAction);
	Map->OnClicked.AddDynamic(this, &UMainUI::MapAction);

	GM = Cast<APartyGameModeBase>(GetWorld()->GetAuthGameMode());

	
}

void UMainUI::DiceAction()
{
	GM->CurrentPlayer->RollDice();
	
}

void UMainUI::ItemAction()
{
	GM->CurrentPlayer->ChooseItem();
}

void UMainUI::MapAction()
{
}
