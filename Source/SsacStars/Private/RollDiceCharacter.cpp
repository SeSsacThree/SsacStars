// Fill out your copyright notice in the Description page of Project Settings.


#include "RollDiceCharacter.h"

#include "Dice.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values

class UStaticMeshComponent;
ARollDiceCharacter::ARollDiceCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 130.0f; // The camera follows at this distance behind the character	
	SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	SpringArm->SetRelativeLocation(FVector(0, 40, 60));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	handComp = CreateDefaultSubobject<USceneComponent>(TEXT("handComp"));
	handComp->SetupAttachment(GetMesh(), TEXT("handComp"));
}

// Called when the game starts or when spawned
void ARollDiceCharacter::BeginPlay()
{
	Super::BeginPlay();


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



	if(Dice)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Dice"));
		GrapDice(Dice);
		Dice->SetOwner(this);
	}
	
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

void ARollDiceCharacter::ThrowDice(const AActor* Actor)
{

	if (nullptr == Actor)
		return;

	auto mesh = Actor->GetComponentByClass<USkeletalMeshComponent>();
	// pistol ������ �Ѱ�ʹ�.
	mesh->SetSimulatePhysics(true);
	// hand���� ����ʹ�.
	mesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	Dice->SetOwner(nullptr);
}


void ARollDiceCharacter::GrapDice(const AActor* Actor)
{

	auto mesh = Actor->GetComponentByClass<USkeletalMeshComponent>();
	mesh->SetSimulatePhysics(false);
	mesh->AttachToComponent(handComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void ARollDiceCharacter::GetSignal()
{
	ThrowDice(Dice);
}

