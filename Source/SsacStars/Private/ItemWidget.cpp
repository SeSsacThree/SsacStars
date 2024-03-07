// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"
#include "Components/Image.h"

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ImageItemSpeedUp->SetVisibility(ESlateVisibility::Hidden);
	ImageItemGetSmall->SetVisibility(ESlateVisibility::Hidden);
	
}
void UItemWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if(bSpeedUp)
	{
		ImageItemSpeedUp->SetVisibility(ESlateVisibility::Visible);
	}

	if(bGetSmall)
	{
		ImageItemGetSmall->SetVisibility(ESlateVisibility::Visible);
	}
}