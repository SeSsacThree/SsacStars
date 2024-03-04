// Fill out your copyright notice in the Description page of Project Settings.


#include "GetCoins.h"
#include "TimerManager.h"

void UGetCoins::NativeConstruct()
{
	Super::NativeConstruct();

	AnimationArray.Add(Image0Animation);
	AnimationArray.Add(Image1Animation);
	AnimationArray.Add(Image2Animation);
	AnimationArray.Add(Image3Animation);
	AnimationArray.Add(Image4Animation);
	AnimationArray.Add(Image5Animation);
	AnimationArray.Add(Image6Animation);
	AnimationArray.Add(Image7Animation);
	AnimationArray.Add(Image8Animation);
	AnimationArray.Add(Image9Animation);

	// DropCoinsNumber = 0;

	if (AnimationArray.IsValidIndex(0))
	{
		DropCoins(Image0Animation);
	}

	GetCoins();
}

void UGetCoins::GetCoins()
{
	// DropCoins(AnimationArray[DropCoinsNumber]);
	DropCoins(AnimationArray[DropCoinsNumber]);

}
void UGetCoins::DropCoins(UWidgetAnimation* InWidgetAnimation)
{
	PlayAnimation(InWidgetAnimation);

	DelayTime(0.1f, [this]()
	{
		if (DropCoinsNumber >= 0 && DropCoinsNumber < AnimationArray.Num())
		{
		// DropCoinsNumber = (DropCoinsNumber + 1) % AnimationArray.Num();
			DropCoins(AnimationArray[DropCoinsNumber]);
			DropCoinsNumber++;
		}else
		{
			return;
		}
	});
}



void UGetCoins::DelayTime(float WantSeconds, TFunction<void()> InFunction)
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [InFunction]()
		{
			// 지연 후 실행될 함수 호출
			InFunction();
		}, WantSeconds, false);
}


