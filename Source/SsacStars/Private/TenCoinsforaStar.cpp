// Fill out your copyright notice in the Description page of Project Settings.


#include "TenCoinsforaStar.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/WrapBox.h"
#include "Animation/WidgetAnimation.h"

void UTenCoinsforaStar::NativeConstruct()
{
	Super::NativeConstruct();

	//��ư�̶� ClickedButton �Լ� ���ε�
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
		//WrapBox ����
		WrapBox->SetVisibility(ESlateVisibility::Hidden);
		//�̹��� ����
		StarImage->SetVisibility(ESlateVisibility::Hidden);
	}

	if (StarImageAnimation)
	{
		//Animation�̶� Delegate ���ε�
		//BindToAnimationFinished(StarImageAnimation, StarAnimationEvent);

		//Delegate�� RemoveWidgetAfterAnimation �Լ� ���ε�
		StarAnimationEvent.BindDynamic(this, &UTenCoinsforaStar::RemoveWidgetAfterAnimation);
		BindToAnimationFinished(StarImageAnimation, StarAnimationEvent);
	}
	// RemoveFromParent();

}

void UTenCoinsforaStar::ClickedButton()
{
	//WrapBox ����
	if (WrapBox)
	{
		WrapBox->SetVisibility(ESlateVisibility::Visible);
	}

	

	// ������ 1��
	FTimerHandle DelayTimerHandle;
	float DelayTime = 1;
	bool bIsLoop = false;

	GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, FTimerDelegate::CreateLambda(
		[this]()->void
		{
			StarImage->SetVisibility(ESlateVisibility::Visible);

			UE_LOG(LogTemp, Warning, TEXT("UTenCoinsforaStar::ClickedButton - Delay"))
			// �� �ִϸ��̼� ����� ���ÿ� WrapBox�� ��ư �����
			GetStarAnimation(StarImageAnimation);

			//Animation ������ �ڵ����� RemoveWidgetAfterAnimation �����
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
	// �ִϸ��̼��� ������
	// ���� �����
	RemoveFromParent();
}
