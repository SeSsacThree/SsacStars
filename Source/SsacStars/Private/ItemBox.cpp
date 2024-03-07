// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBox.h"

#include "ItemWidget.h"
#include "KartPlayer.h"
#include "MiniGameItem_SpeedUp.h"
#include "Components/BoxComponent.h"
#include "Components/SlateWrapperTypes.h"
#include "Components/StaticMeshComponent.h"
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
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AItemBox::OnMyCompBeginOverlap);
}

// Called every frame
void AItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(!bItemBox)
	{
		currentTime += GetWorld()->GetDeltaSeconds();
		itemBox->SetVisibility(false);
		boxComp->SetGenerateOverlapEvents(false);

		if(currentTime>delayTime)
		{
			itemBox->SetVisibility(true);
			boxComp->SetGenerateOverlapEvents(true);
			bItemBox = true;
			currentTime = 0;
		}
	}

}

void AItemBox::OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 만약 OtherActor가 플레이어라면
	if (OtherActor->IsA<AKartPlayer>())
	{
		auto player = Cast<AKartPlayer>(OtherActor);

		bItemBox = false;

		//플레이어가 아이템이 없다면
		if(false==player->hasItem)
		{
			player->hasItem = true;
			UE_LOG(LogTemp, Warning, TEXT("hasItem : True"));

			//랜덤 아이템 얻기
			GetRandomItem();

			//UGameplayStatics::PlaySound2D(GetWorld(), itemBoxSound);
		}
		else
		{
			return;
		}
		
	}
}

void AItemBox::GetRandomItem()
{
	int index = rand() % 2;

	//auto itemWidget = Cast<UItemWidget>(UGameplayStatics::GetActorOfClass(GetWorld(), UItemWidget::StaticClass()));
	//auto player= Cast<AKartPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AKartPlayer::StaticClass()));
	UE_LOG(LogTemp, Warning, TEXT("random ok"));
	switch (index)
	{
	case 0:
		//speedUp 
		//player->speedUp();
		if(itemWidget){
			UE_LOG(LogTemp, Warning, TEXT("Item : speedup"));
			itemWidget->bSpeedUp = true;
		}
		break;
	case 1:
		//getSmall
		if (itemWidget) {
			UE_LOG(LogTemp, Warning, TEXT("Item : get small"));
			itemWidget->bGetSmall = true;
		}
		break;
	//case 2:
	//	//
	//	break;
	//case 3:
	//	break;
	}

}
