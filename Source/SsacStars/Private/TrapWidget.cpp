// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapWidget.h"
#include "Components/Button.h"
#include "TimerManager.h"
// #include "Developer/CookedEditor/Public/CookedEditorTargetPlatform.h"

void UTrapWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AnimationArray.Add(ThirdTrapButtonAnimation);
	AnimationArray.Add(SecondTrapButtonAnimation);
	AnimationArray.Add(FirstTrapButtonAnimation);

	RandomNumber = FMath::RandRange(10, 15);
	RandomPickTrap();
}

void UTrapWidget::BlinkTrapButton(UWidgetAnimation* InWidgetAnimation)
{
	PlayAnimation(InWidgetAnimation);

	DelayTime(0.3f, [this]()
		{
			RandomNumber--;
			if (RandomNumber > 0)
				RandomPickTrap();
		});
}

void UTrapWidget::RandomPickTrap()
{
	BlinkTrapButton(AnimationArray[RandomNumber % 3]);
}

void UTrapWidget::DelayTime(float WantSeconds, TFunction<void()> InFunction)
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [InFunction]()
		{
			// 지연 후 실행될 함수 호출
			InFunction();
		}, WantSeconds, false);
}
