// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomItemWidget.h"

#include "Animation/WidgetAnimation.h"
#include "Components/Button.h"

void URandomItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AnimationArray.Add(ButtonThreeBlinkAnimation);
	AnimationArray.Add(ButtonTwoBlinkAnimation);
	AnimationArray.Add(ButtonOneBlinkAnimation);

	RandomNumber = FMath::RandRange(10, 15);
	RandomPickItem();

	//TimerDelegate.BindUFunction(this, "BlinkButton", OutWidgetAnimation);


}

// 넘겨 받은 WidgetAnimation을 실행하기
void URandomItemWidget::BlinkButton(UWidgetAnimation* InWidgetAnimation)
{
	PlayAnimation(InWidgetAnimation);

	DelayTime(0.3f, [this]()
		{
			RandomNumber--;
			if (RandomNumber > 0)
				RandomPickItem();

		});
}

void URandomItemWidget::RandomPickItem()
{

	BlinkButton(AnimationArray[RandomNumber % 3]);
}

void URandomItemWidget::DelayTime(float WantSeconds, TFunction<void()> InFunction)
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [InFunction]()
		{
			// 지연 후 실행될 함수 호출
			InFunction();
		}, WantSeconds, false);
}





