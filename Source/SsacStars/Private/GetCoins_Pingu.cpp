// Fill out your copyright notice in the Description page of Project Settings.


#include "GetCoins_Pingu.h"

void UGetCoins_Pingu::NativeConstruct()
{
	Super::NativeConstruct();

	AnimationArray.Add(Image_PinguAnimation0);
	AnimationArray.Add(Image_PinguAnimation1);
	AnimationArray.Add(Image_PinguAnimation2);
	AnimationArray.Add(Image_PinguAnimation3);
	AnimationArray.Add(Image_PinguAnimation4);
	AnimationArray.Add(Image_PinguAnimation5);
	AnimationArray.Add(Image_PinguAnimation6);
	AnimationArray.Add(Image_PinguAnimation7);
	AnimationArray.Add(Image_PinguAnimation8);
	AnimationArray.Add(Image_PinguAnimation9);

	if (AnimationArray.IsValidIndex(0))
	{
		DropCoins(Image_PinguAnimation0);
	}

	GetCoins();
}

void UGetCoins_Pingu::GetCoins()
{
	DropCoins(AnimationArray[DropCoinsNumber]);
}

void UGetCoins_Pingu::DropCoins(UWidgetAnimation* InWidgetAnimation)
{
	PlayAnimation(InWidgetAnimation);

	DelayTime(0.1f, [this]()
		{
			if (DropCoinsNumber >= 0 && DropCoinsNumber < AnimationArray.Num())
			{
				// DropCoinsNumber = (DropCoinsNumber + 1) % AnimationArray.Num();
				DropCoins(AnimationArray[DropCoinsNumber]);
				DropCoinsNumber++;
			}
			else
			{
				SetVisibility(ESlateVisibility::Hidden);
				return;
			}
		});
}

void UGetCoins_Pingu::DelayTime(float WantSeconds, TFunction<void()> InFunction)
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [InFunction]()
		{
			// 지연 후 실행될 함수 호출
			InFunction();
		}, WantSeconds, false);
}
