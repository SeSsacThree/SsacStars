// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomItemWidget.h"

#include "Animation/WidgetAnimation.h"
#include "Components/Button.h"

void URandomItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AnimationArray.Add(ButtonOneBlinkAnimation);
	AnimationArray.Add(ButtonTwoBlinkAnimation);
	AnimationArray.Add(ButtonThreeBlinkAnimation);

	RandomPickItem();
}

// 넘겨 받은 WidgetAnimation을 실행하기
void URandomItemWidget::BlinkButton(UWidgetAnimation* InWidgetAnimation)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *InWidgetAnimation->GetName())

	PlayAnimation(InWidgetAnimation);
}

void URandomItemWidget::RandomPickItem()
{
	int RandomNumber = FMath::RandRange(10,15);

	UE_LOG(LogTemp, Warning, TEXT("%d"), RandomNumber)
	for (int i = 0; i < RandomNumber; i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d"), i)
		int ButtonIndex = i % 3;
		BlinkButton(AnimationArray[ButtonIndex]);
	}
}
 
