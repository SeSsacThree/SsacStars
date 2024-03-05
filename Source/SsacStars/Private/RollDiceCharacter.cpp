// Fill out your copyright notice in the Description page of Project Settings.


#include "RollDiceCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Dice.h"
#include "Components/SceneCaptureComponent2D.h"
#include "ThrowDiceCharacterUi.h"
#include "Kismet/GameplayStatics.h"
// Sets default values

class UStaticMeshComponent;
ARollDiceCharacter::ARollDiceCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));
	SceneCaptureComponent->SetupAttachment(RootComponent);

	handComp = CreateDefaultSubobject<USceneComponent>(TEXT("handComp"));
	handComp->SetupAttachment(GetMesh(), TEXT("handComp"));



}

// Called when the game starts or when spawned
void ARollDiceCharacter::BeginPlay()
{
	Super::BeginPlay();

	ThrowDiceUi = NewObject<UThrowDiceCharacterUi>(this, ThrowDiceUiFactory);

	CreateDice();


	
}

// Called every frame
void ARollDiceCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARollDiceCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARollDiceCharacter::CreateDice()
{
	Dice = Cast<ADice>(UGameplayStatics::GetActorOfClass(GetWorld(), ADice::StaticClass()));

	/*
	TArray<struct FOverlapResult> OutOverlaps;
	FCollisionObjectQueryParams ObjectQueryParams(FCollisionObjectQueryParams::InitType::AllObjects);
	bool bHits = GetWorld()->OverlapMultiByObjectType(
		OutOverlaps,
		GetActorLocation(),
		FQuat::Identity,
		ObjectQueryParams,
		FCollisionShape::MakeSphere(100));

	if (bHits)
	{
		// 전체 검색해서
		for (auto result : OutOverlaps)
		{

			// 만약 액터의 이름에 BP_Dice이 포함되어있다면
			if (result.GetActor()->GetActorNameOrLabel().Contains(TEXT("BP_Dice")))
			{
				// 그것을 grabPistol로 하고싶다.
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("overlap"));
				Dice = result.GetActor();
				// 반복을 그만하고싶다.
				break;
			}
		}
	}
	*/


	if (Dice)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Dice"));
		GrapDice(Dice);
	}


}

void ARollDiceCharacter::ThrowDice(const AActor* Actor)
{

	if (nullptr == Actor)
		return;
	//Dice->SetActorEnableCollision(false);

	auto mesh = Actor->GetComponentByClass<USkeletalMeshComponent>();
	// pistol 물리를 켜고싶다.
	mesh->SetSimulatePhysics(true);
	//mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	//mesh->SetCollisionResponseToAllChannels(ECR_Block);
	// hand에서 떼고싶다.
	mesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	
	
}


void ARollDiceCharacter::GrapDice(const AActor* Actor)
{
	Dice->IsStopRollingMode = false;
	auto mesh = Actor->GetComponentByClass<USkeletalMeshComponent>();
	mesh->SetSimulatePhysics(false);
	mesh->AttachToComponent(handComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
}

void ARollDiceCharacter::GetSignal()
{
	ThrowDice(Dice);
	Dice->ThrowDice();
}

void ARollDiceCharacter::StartRolling()
{
	Dice->StartDiceRolling();
}

void ARollDiceCharacter::AddView()
{
	if(ThrowDiceUi)
		ThrowDiceUi->AddToViewport();

}

void ARollDiceCharacter::CloseView()
{
	GrapDice(Dice);
	ThrowDiceUi->RemoveFromParent();
}

void ARollDiceCharacter::Jump(float LaunchAmount)
{
	FVector LaunchDirection = FVector::UpVector; // 위쪽으로 띄우기 예시
	float LaunchStrength = LaunchAmount; // 띄우는 힘의 크기

	LaunchCharacter(LaunchDirection * LaunchStrength, false, false);
}

