// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapWidget.h"

#include "GetCoins.h"
#include "Map_SpaceFunction.h"
#include "PartyGameModeBase.h"
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

	APartyGameModeBase* GM=Cast<APartyGameModeBase>(GetWorld()->GetAuthGameMode());

	// RandomNumber�� 1�϶� ����Ǵ� �ִϸ��̼��� �ش� ����� ����
	if (GM)
	{
		if (RandomNumber == 1)
		{
			switch (RandomNumber % 3)
			{
				case 0:
						oneOfThreeTraps->FirstTrap(GM->CurrentPlayer);
						break;
					
				case 1:
						oneOfThreeTraps->SecondTrap(GM->CurrentPlayer);
						break;
					
				case 2:
						oneOfThreeTraps->ThirdTrap(GM->CurrentPlayer);
						break;
			}
		}
		
	}
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
			// ���� �� ����� �Լ� ȣ��
			InFunction();
		}, WantSeconds, false);
}

