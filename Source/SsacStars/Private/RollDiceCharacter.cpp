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
		// ��ü �˻��ؼ�
		for (auto result : OutOverlaps)
		{

			// ���� ������ �̸��� BP_Dice�� ���ԵǾ��ִٸ�
			if (result.GetActor()->GetActorNameOrLabel().Contains(TEXT("BP_Dice")))
			{
				// �װ��� grabPistol�� �ϰ�ʹ�.
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("overlap"));
				Dice = result.GetActor();
				// �ݺ��� �׸��ϰ�ʹ�.
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
	// pistol ������ �Ѱ�ʹ�.
	mesh->SetSimulatePhysics(true);
	//mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	//mesh->SetCollisionResponseToAllChannels(ECR_Block);
	// hand���� ����ʹ�.
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
	FVector LaunchDirection = FVector::UpVector; // �������� ���� ����
	float LaunchStrength = LaunchAmount; // ���� ���� ũ��

	LaunchCharacter(LaunchDirection * LaunchStrength, false, false);
}

