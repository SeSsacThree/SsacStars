// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUiCard.h"

#include "PartyGameModeBase.h"
#include "PartyPlayer.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"

void UPlayerUiCard::NativeConstruct()
{
	Super::NativeConstruct();


	//GM = Cast<APartyGameModeBase>(GetWorld()->GetAuthGameMode());
	/*
	if(GM->InitialTurnOrder[TurnIndex])
		CurrentPlayer = GM->InitialTurnOrder[TurnIndex];
		*/
}

void UPlayerUiCard::SetStarScoreText(int32 score)
{
	StarScore->SetText(FText::AsNumber (score));
	
}

void UPlayerUiCard::SetCoinScoreText(int32 score)
{
	CoinScore->SetText(FText::AsNumber(score));
}

void UPlayerUiCard::SetMainScoreText(int32 score)
{
	MainScore->SetText(FText::AsNumber(score));
}

void UPlayerUiCard::SetTurnOrderScoreText(int32 Score)
{
	TurnOrderScore->SetText(FText::AsNumber(Score));
}

void UPlayerUiCard::SetSpaceTypeBorder(APartyPlayer* Player)
{
	switch (Player->CurrentSpace->SpaceState)
	{
		case ESpaceState::Star:
			{
				SpaceType->SetBrushColor(FLinearColor(1,1 ,0 ));
				break;
			}
		case ESpaceState::Blue:
		{
			SpaceType->SetBrushColor(FLinearColor(0,0 ,1 ));
			break;
		}
		case ESpaceState::Red:
		{
			SpaceType->SetBrushColor(FLinearColor(1,0 ,0 ));
			break;
		}
		case ESpaceState::Item:
		{
			SpaceType->SetBrushColor(FLinearColor(0.5,0.5 ,0 ));
			break;
		}
		case ESpaceState::Trap:
		{
			SpaceType->SetBrushColor(FLinearColor(0,0.5 ,0 ));
			break;
		}
		case ESpaceState::Warp:
		{
			SpaceType->SetBrushColor(FLinearColor(0,0 ,0.3 ));
			break;
		}
	}




}
