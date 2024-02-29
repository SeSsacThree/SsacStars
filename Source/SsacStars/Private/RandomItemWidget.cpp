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

// �Ѱ� ���� WidgetAnimation�� �����ϱ�
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
			// ���� �� ����� �Լ� ȣ��
			InFunction();
		}, WantSeconds, false);
}





