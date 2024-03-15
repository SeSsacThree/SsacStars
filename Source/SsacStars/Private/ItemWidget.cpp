// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"

#include "KartPlayer.h"
#include "Components/Image.h"
#include "Net/UnrealNetwork.h"

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ImageItemSpeedUp->SetVisibility(ESlateVisibility::Hidden);
	ImageItemGetSmall->SetVisibility(ESlateVisibility::Hidden);
	ImageQuestion->SetVisibility(ESlateVisibility::Hidden);
}



void UItemWidget::Init()
{
	ImageItemSpeedUp->SetVisibility(ESlateVisibility::Hidden);
	ImageItemGetSmall->SetVisibility(ESlateVisibility::Hidden);
	ImageQuestion->SetVisibility(ESlateVisibility::Hidden);
	UE_LOG(LogTemp, Warning, TEXT("UItemWidget::Init()"));
}

void UItemWidget::hideQuestion()
{
	ImageQuestion->SetVisibility(ESlateVisibility::Hidden);
	StopAnimation(A_Button);
}
//------------------------------------------------------------------
void UItemWidget::speedUp()
{
	PlayAnimation(A_Button);
	ImageQuestion->SetVisibility(ESlateVisibility::Visible);

	GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, FTimerDelegate::CreateLambda(
		[this]()->void
	{
		ImageItemSpeedUp->SetVisibility(ESlateVisibility::Visible);
		hideQuestion();
	}
	), DelayTime, bIsLoop);
}

//------------------------------------------------------------------
void UItemWidget::shooting()
{
	PlayAnimation(A_Button);
	ImageQuestion->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, FTimerDelegate::CreateLambda(
		[this]()->void
		{
			ImageItemGetSmall->SetVisibility(ESlateVisibility::Visible);
			hideQuestion();
		}
	), DelayTime, bIsLoop);
}




