// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"
#include "Components/Image.h"

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ImageItemSpeedUp->SetVisibility(ESlateVisibility::Hidden);
	ImageItemGetSmall->SetVisibility(ESlateVisibility::Hidden);
	ImageQuestion->SetVisibility(ESlateVisibility::Hidden);
}
void UItemWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bSpeedUp)
	{
		currentTime += GetWorld()->GetDeltaSeconds();

		if (currentTime > delayTime)
		{
			ImageItemSpeedUp->SetVisibility(ESlateVisibility::Visible);
			hideQuestion();
			currentTime = 0;
			bSpeedUp = false;
		}

	}
	if (bGetSmall)
	{
		currentTime += GetWorld()->GetDeltaSeconds();
		
		if (currentTime > delayTime)
		{
			ImageItemGetSmall->SetVisibility(ESlateVisibility::Visible);
			hideQuestion();
			currentTime = 0;
			bGetSmall = false;
		}

	}

}


void UItemWidget::Init()
{
	ImageItemSpeedUp->SetVisibility(ESlateVisibility::Hidden);
	ImageItemGetSmall->SetVisibility(ESlateVisibility::Hidden);
	ImageQuestion->SetVisibility(ESlateVisibility::Hidden);
}

void UItemWidget::hideQuestion()
{
	ImageQuestion->SetVisibility(ESlateVisibility::Hidden);
	StopAnimation(A_Button);
}

void UItemWidget::speedUp()
{
	PlayAnimation(A_Button);
	ImageQuestion->SetVisibility(ESlateVisibility::Visible);
	bSpeedUp = true;
}

void UItemWidget::getSmall()
{
	PlayAnimation(A_Button);
	ImageQuestion->SetVisibility(ESlateVisibility::Visible);
	bGetSmall = true;
}
