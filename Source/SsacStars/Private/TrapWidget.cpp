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

	
	// UE_LOG(LogTemp, Warning, TEXT("ArrayIndex: %d"), ArrayIndex)
	RandomNumber = FMath::RandRange(10, 15);
	ArrayIndex = RandomNumber;

	RandomPickTrap();
	// RemoveFromParent();

	GM = Cast<APartyGameModeBase>(GetWorld()->GetAuthGameMode());
}

void UTrapWidget::BlinkTrapButton(UWidgetAnimation* InWidgetAnimation)
{
	PlayAnimation(InWidgetAnimation);

	DelayTime(0.3f, [this]()
		{
			RandomNumber--;

			if ((RandomNumber > 0) && (RandomNumber != 1)) 
			{
				RandomPickTrap();
			}
			else if ((RandomNumber > 0) && (RandomNumber == 1))
			{
				ApplyTrap(ArrayIndex);
				RemoveFromParent();
			}

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

void UTrapWidget::ApplyTrap(int32 InArrayNumber)
{
	// RandomNumber가 1일때 실행되는 애니메이션의 해당 기능을 실행
	if (GM)
	{
		if (RandomNumber == 1)		//Random == 1		
		{
			UE_LOG(LogTemp, Warning, TEXT("InArrayNumber: %d"), InArrayNumber)

				//switch (RandomNumber % 3) // Random == 1, 2, 3
				switch (InArrayNumber % 3)
				{
				case 0:
					oneOfThreeTraps->FirstTrap(GM->CurrentPlayer);
					UE_LOG(LogTemp, Warning, TEXT("aaaaaa"))
						break;
				case 1:
					oneOfThreeTraps->SecondTrap(GM->CurrentPlayer);
					UE_LOG(LogTemp, Warning, TEXT("bbbbb"))
						break;
				case 2:
					oneOfThreeTraps->ThirdTrap(GM->CurrentPlayer);
					UE_LOG(LogTemp, Warning, TEXT("ccccc"))
						break;
				}
		}
	}
}

void UTrapWidget::RemoveWidgetAfterAnimation()
{
	UE_LOG(LogTemp, Warning, TEXT("URandomItemWidget::RemoveWidgetAfterAnimation"))
		// 애니메이션이 끝나면
		// 위젯 사라짐
		RemoveFromParent();
}

