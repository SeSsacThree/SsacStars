// Fill out your copyright notice in the Description page of Project Settings.


#include "TenCoinsforaStar.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/WrapBox.h"
#include "Animation/WidgetAnimation.h"

void UTenCoinsforaStar::NativeConstruct()
{
	Super::NativeConstruct();

	//버튼이랑 ClickedButton 함수 바인딩
	if (Button)
	{
		Button->OnClicked.AddDynamic(this, &UTenCoinsforaStar::ClickedButton);
	}
	if (PassButton)
	{
		PassButton->OnClicked.AddDynamic(this, &UTenCoinsforaStar::ClickedPassButton);
	}

	if(WrapBox && StarImage)
	{
		//WrapBox 숨김
		WrapBox->SetVisibility(ESlateVisibility::Hidden);
		//이미지 숨김
		StarImage->SetVisibility(ESlateVisibility::Hidden);
	}

	if (StarImageAnimation)
	{
		//Animation이랑 Delegate 바인딩
		//BindToAnimationFinished(StarImageAnimation, StarAnimationEvent);

		//Delegate랑 RemoveWidgetAfterAnimation 함수 바인딩
		StarAnimationEvent.BindDynamic(this, &UTenCoinsforaStar::RemoveWidgetAfterAnimation);
		BindToAnimationFinished(StarImageAnimation, StarAnimationEvent);
	}
	// RemoveFromParent();

}

void UTenCoinsforaStar::ClickedButton()
{
	//WrapBox 보임
	if (WrapBox)
	{
		WrapBox->SetVisibility(ESlateVisibility::Visible);
	}

	

	// 딜레이 1초
	FTimerHandle DelayTimerHandle;
	float DelayTime = 1;
	bool bIsLoop = false;

	GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, FTimerDelegate::CreateLambda(
		[this]()->void
		{
			StarImage->SetVisibility(ESlateVisibility::Visible);

			UE_LOG(LogTemp, Warning, TEXT("UTenCoinsforaStar::ClickedButton - Delay"))
			// 별 애니메이션 실행과 동시에 WrapBox랑 버튼 사라짐
			GetStarAnimation(StarImageAnimation);

			//Animation 끝나면 자동으로 RemoveWidgetAfterAnimation 실행됨
		}
	), DelayTime, bIsLoop);
	


	
	

}


void UTenCoinsforaStar::GetStarAnimation(UWidgetAnimation* InWidgetAnimation)
{
	UE_LOG(LogTemp, Warning, TEXT("UTenCoinsforaStar::GetStarAnimation"))
	PlayAnimation(InWidgetAnimation);
}

void UTenCoinsforaStar::ClickedPassButton()
{
	UE_LOG(LogTemp, Warning, TEXT("UTenCoinsforaStar::ClickedPassButton"))
	RemoveWidgetAfterAnimation();
}

void UTenCoinsforaStar::RemoveWidgetAfterAnimation()
{
	UE_LOG(LogTemp, Warning, TEXT("UTenCoinsforaStar::RemoveWidgetAfterAnimation"))
	// 애니메이션이 끝나면
	// 위젯 사라짐
	RemoveFromParent();
}
