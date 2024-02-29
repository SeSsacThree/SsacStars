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
	// pistol 물리를 켜고싶다.
	mesh->SetSimulatePhysics(true);
	// hand에서 떼고싶다.
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

