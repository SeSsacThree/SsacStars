// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomItemWidget.h"

#include "Map_SpaceFunction.h"
#include "PartyGameModeBase.h"
#include "TenCoinsforaStar.h"
#include "Animation/WidgetAnimation.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void URandomItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AnimationArray.Add(ButtonThreeBlinkAnimation);
	AnimationArray.Add(ButtonTwoBlinkAnimation);
	AnimationArray.Add(ButtonOneBlinkAnimation);

	RandomNumber = FMath::RandRange(10, 15);
	ArrayIndex = RandomNumber;

	RandomPickItem();
	// RemoveFromParent();

	GM = Cast<APartyGameModeBase>(GetWorld()->GetAuthGameMode());
	oneOfRandomItems=Cast<AMap_SpaceFunction>(UGameplayStatics::GetActorOfClass(GetWorld(), AMap_SpaceFunction::StaticClass()));
	// removeWidget=Cast<UTenCoinsforaStar>(UGameplayStatics::GetActorOfClass(GetWorld(), UTenCoinsforaStar::StaticClass()));

	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMap_SpaceFunction::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
	{
		oneOfRandomItems = Cast<AMap_SpaceFunction>(FoundActors[0]);
	}
	else
	{
		oneOfRandomItems = GetWorld()->SpawnActor<AMap_SpaceFunction>(AMap_SpaceFunction::StaticClass());

	}
	
}

// 넘겨 받은 WidgetAnimation을 실행하기
void URandomItemWidget::BlinkButton(UWidgetAnimation* InWidgetAnimation)
{
	PlayAnimation(InWidgetAnimation);

	DelayTime(0.3f, [this]()
		{
			RandomNumber--;
			if ((RandomNumber > 0) && (RandomNumber != 1)) 
			{
				RandomPickItem();
			}
			else if ((RandomNumber > 0) && (RandomNumber == 1))
			{
				ApplyTrap(ArrayIndex);
				RemoveWidgetAfterAnimation();
			}
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

void URandomItemWidget::ApplyTrap(int32 InArrayNumber)
{
	/*
	if (oneOfRandomItems)
	{
		return;
	}*/

	if (!oneOfRandomItems)
	{
		UE_LOG(LogTemp, Error, TEXT("No instance of AMap_SpaceFunction found. Trap cannot be applied."));
		return;
	}



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
					oneOfRandomItems->PlusThreeSpaces(GM->CurrentPlayer);
					UE_LOG(LogTemp, Warning, TEXT("aaaaaa"))
				
						break;
					
				case 1:
					oneOfRandomItems->SwapToStar(GM->CurrentPlayer);
					UE_LOG(LogTemp, Warning, TEXT("bbbbb"))
				
						break;
						
				case 2:
					oneOfRandomItems->SwapPlayerPositions(GM->CurrentPlayer);
					UE_LOG(LogTemp, Warning, TEXT("ccccc"))
				
						break;
				}
		}
	}

}

void URandomItemWidget::RemoveWidgetAfterAnimation()
{
	UE_LOG(LogTemp, Warning, TEXT("URandomItemWidget::RemoveWidgetAfterAnimation"))
		// 애니메이션이 끝나면
		// 위젯 사라짐
		RemoveFromParent();
}