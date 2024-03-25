// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUiCard.h"


#include "PartyGameModeBase.h"
#include "PartyPlayer.h"
#include "Components/Border.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "PartyGameStateBase.h"

void UPlayerUiCard::NativeConstruct()
{
	Super::NativeConstruct();
	
	PartyGameState = Cast<APartyGameStateBase>(GetWorld()->GetGameState());
	GM = Cast<APartyGameModeBase>(GetWorld()->GetAuthGameMode());

}

void UPlayerUiCard::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


}

void UPlayerUiCard::SetStarScoreText(int32 score)
{
	StarScore->SetText(FText::AsNumber(score));

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


	if (TurnIndex == Score)
	{
		TurnOrderScore->SetText( FText::FromString( TEXT( "MyTurn" ) ) );
		MyTurnColor->SetRenderOpacity( 1 );
	}
	else
	{
		TurnOrderScore->SetText(FText::FromString(TEXT("")));
		MyTurnColor->SetRenderOpacity( 0 );
	}

}

void UPlayerUiCard::SetSpaceTypeBorder(APartyPlayer* Player)
{
	switch (Player->CurrentSpace->SpaceState)
	{
	case ESpaceState::Star:
	{
		SpaceType->SetBrushColor(FLinearColor(1, 1, 0));
		break;
	}
	case ESpaceState::Blue:
	{
		SpaceType->SetBrushColor(FLinearColor(0, 0, 1));
		break;
	}
	case ESpaceState::Red:
	{
		SpaceType->SetBrushColor(FLinearColor(1, 0, 0));
		break;
	}
	case ESpaceState::Item:
	{
		SpaceType->SetBrushColor(FLinearColor(0.5, 0.5, 0));
		break;
	}
	case ESpaceState::Trap:
	{
		SpaceType->SetBrushColor(FLinearColor(0, 0.5, 0));
		break;
	}
	case ESpaceState::Warp:
	{
		SpaceType->SetBrushColor(FLinearColor(0, 0, 0.3));
		break;
	}
	}




}

void UPlayerUiCard::SetProfile(int Index)
{
	switch (Index)
	{
	case 0:
	{

		break;
	}
	case 1:
	{

		break;
	}
	case 2:
	{

		break;
	}
	case 3:
	{

		break;
	}
	}

}

