// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBox.h"

#include "ItemWidget.h"
#include "KartPlayer.h"
#include "MiniGameItem_SpeedUp.h"
#include "Components/BoxComponent.h"
#include "Components/SlateWrapperTypes.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AItemBox::AItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	this->SetRootComponent(boxComp);
	boxComp->SetGenerateOverlapEvents(true);
	boxComp->SetCollisionProfileName(TEXT("ItemBox"));


	itemBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemBox"));
	itemBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	itemBox->SetupAttachment(RootComponent);;
	
	
}

// Called when the game starts or when spawned
void AItemBox::BeginPlay()
{
	Super::BeginPlay();
	
	//boxComponent와 begin overlap함수 바인딩하기
	boxComp->OnComponentEndOverlap.AddDynamic(this, &AItemBox::OnMyCompEndOverlap);
}

// Called every frame
void AItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AItemBox::OnMyCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AKartPlayer* OverlapPlayer = Cast<AKartPlayer>(OtherActor)) {
		if (!OverlapPlayer->GetController()) { return; }
		if (OverlapPlayer->GetController()->IsLocalPlayerController()) {

			bItemBox = false;

			//플레이어가 아이템이 없을때만
			if (false == OverlapPlayer->hasItem)
			{
				OverlapPlayer->hasItem = true;

				//랜덤 아이템 얻기
				GetRandomItem(OverlapPlayer);

				//UGameplayStatics::PlaySound2D(GetWorld(), itemBoxSound);
			}
			else
			{
				return;
			}

			itemBox->SetVisibility(false);
			boxComp->SetGenerateOverlapEvents(false);

			if (!GEngine) { return; }
			FString PlayerStateName = FString::Printf(TEXT("Player State ID: %d"), OverlapPlayer->GetPlayerState()->GetPlayerId());
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, PlayerStateName);

		}
	}
}

void AItemBox::GetRandomItem(AKartPlayer* inKartPlayer)
{
	int index = rand() % 2;

	UE_LOG(LogTemp, Warning, TEXT("AItemBox::GetRandomItem - %s"), *inKartPlayer->GetName());

	switch (index)
	{
	case 0:
		//speed up
		if (itemWidget) {
			//Item : speedup
			itemWidget->speedUp();
			inKartPlayer->itemNumber = 1;
		}
		break;
	case 1:
		//shooting
		if (itemWidget) {
			itemWidget->shooting();
			inKartPlayer->itemNumber = 2;
		}
		break;
	}


	FTimerHandle DelayTimerHandle;
	//2초 Delay
	float DelayTime = 2;
	//Looping 여부
	bool bIsLoop = false;

	//Lambda 함수 구조 [REFERENCE 또는 CAPTURE]()-> Return 타입 {구현부}
	GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, FTimerDelegate::CreateLambda(
		[this]()->void
		{
			itemBox->SetVisibility(true);
			boxComp->SetGenerateOverlapEvents(true);
			bItemBox = true;
			currentTime = 0;
		}
	), DelayTime, bIsLoop);

	//ServerGetRandomItem(index);
	

}
