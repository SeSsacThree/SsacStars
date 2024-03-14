// Fill out your copyright notice in the Description page of Project Settings.


#include "RollDiceCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Dice.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SceneCaptureComponent.h"
#include "ThrowDiceCharacterUi.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
// Sets default values

class UStaticMeshComponent;
ARollDiceCharacter::ARollDiceCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));
	this->SetRootComponent(SceneCaptureComponent);


	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(SceneCaptureComponent);

	handComp = CreateDefaultSubobject<USceneComponent>(TEXT("handComp"));
	handComp->SetupAttachment(MeshComp);



}

// Called when the game starts or when spawned
void ARollDiceCharacter::BeginPlay()
{
	Super::BeginPlay();
	Dice = Cast<ADice>(UGameplayStatics::GetActorOfClass(GetWorld(), ADice::StaticClass()));
	ThrowDiceUi = NewObject<UThrowDiceCharacterUi>(this, ThrowDiceUiFactory);

	ServerCreateDice();
	//CreateDice();
	BeginLocation = GetActorLocation();


}

// Called every frame
void ARollDiceCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SceneCaptureComponent->ShowOnlyActorComponents(this);
	SetActorLocation(FVector(BeginLocation.X, BeginLocation.Y, GetActorLocation().Z));
}

// Called to bind functionality to input
/*
void ARollDiceCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
*/
void ARollDiceCharacter::CreateDice()
{

	//Dice = Cast<ADice>(UGameplayStatics::GetActorOfClass(GetWorld(), ADice::StaticClass()));

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
		//GrapDice(Dice);
		ServerGrabDice(Dice);
	}


}
void ARollDiceCharacter::ServerCreateDice_Implementation()
{
	MultiCreateDice();
}

void ARollDiceCharacter::MultiCreateDice_Implementation()
{


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
		//GrapDice(Dice);
		ServerGrabDice(Dice);
	}
}

void ARollDiceCharacter::ThrowDice(const AActor* Actor)
{
	/*
	if (nullptr == Actor)
		return;
	//Dice->SetActorEnableCollision(false);

	auto mesh = Actor->GetComponentByClass<USkeletalMeshComponent>();
	// pistol ������ �Ѱ�ʹ�.
	//mesh->SetSimulatePhysics(true);
	//mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	//mesh->SetCollisionResponseToAllChannels(ECR_Block);
	// hand���� ����ʹ�.
	mesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Throw"));
	*/

}
void ARollDiceCharacter::ServerThrowDice_Implementation(const AActor* Actor)
{
	MultiThrowDice(Actor);
}

void ARollDiceCharacter::MultiThrowDice_Implementation(const AActor* Actor)
{
	if (nullptr == Actor)
		return;
	//Dice->SetActorEnableCollision(false);

	auto mesh = Actor->GetComponentByClass<USkeletalMeshComponent>();
	// pistol ������ �Ѱ�ʹ�.
	//mesh->SetSimulatePhysics(true);
	//mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	//mesh->SetCollisionResponseToAllChannels(ECR_Block);
	// hand���� ����ʹ�.
	mesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Throw"));
}

void ARollDiceCharacter::GrapDice(const AActor* Actor)
{
	/*
	Dice->ReBack();
	Dice->IsStopRollingMode = false;
	auto mesh = Actor->GetComponentByClass<USkeletalMeshComponent>();
	//mesh->SetSimulatePhysics(false);
	mesh->AttachToComponent(handComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GrabDice"));
	*/
}

void ARollDiceCharacter::ServerGrabDice_Implementation(const AActor* Actor)
{
	MultiGrabDice(Actor);
}

void ARollDiceCharacter::MultiGrabDice_Implementation(const AActor* Actor)
{
	Dice->ReBack();
	Dice->IsStopRollingMode = false;
	auto mesh = Actor->GetComponentByClass<USkeletalMeshComponent>();
	//mesh->SetSimulatePhysics(false);
	mesh->AttachToComponent(handComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GrabDice"));
}
void ARollDiceCharacter::GetSignal()
{
	ServerThrowDice(Dice);
	//ThrowDice(Dice);
	//Dice->ThrowDice();
	Dice->ServerThrowDice();
	//Dice->IsUpMode = true;
}

void ARollDiceCharacter::StartRolling()
{
	//Dice->StartDiceRolling();
	Dice->MultiStartDiceRolling();
}

void ARollDiceCharacter::AddView()
{
	if (ThrowDiceUi)
		ThrowDiceUi->AddToViewport();

}

void ARollDiceCharacter::CloseView()
{




	DelayTime(1.0f, [this]()
		{
			//��ȯ�ʿ�
			ServerGrabDice(Dice);
			//GrapDice(Dice);
			ServerRemoveThrowDiceUi();
			//ThrowDiceUi->RemoveFromParent();

		});

}

void ARollDiceCharacter::Jump(float LaunchAmount)
{
	FVector LaunchDirection = FVector::UpVector; // �������� ���� ����
	float LaunchStrength = LaunchAmount; // ���� ���� ũ��


}

void ARollDiceCharacter::DelayTime(float WantSeconds, TFunction<void()> InFunction)
{

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [InFunction]()
		{
			// ���� �� ����� �Լ� ȣ��
			InFunction();
		}, WantSeconds, false);
}



void ARollDiceCharacter::ServerRemoveThrowDiceUi_Implementation()
{
	MultiRemoveThrowDiceUi();
}

void ARollDiceCharacter::MultiRemoveThrowDiceUi_Implementation()
{
	ThrowDiceUi->RemoveFromParent();
}

void ARollDiceCharacter::ServerViewThrowDiceUi_Implementation()
{
	MultiViewThrowDiceUi();
}

void ARollDiceCharacter::MultiViewThrowDiceUi_Implementation()
{
	ThrowDiceUi->AddToViewport();
}




void ARollDiceCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ARollDiceCharacter, Dice);
	DOREPLIFETIME(ARollDiceCharacter, ThrowDiceUi);
}
