// Fill out your copyright notice in the Description page of Project Settings.


#include "Dice.h"
#include "Components/SceneCaptureComponent2D.h"
#include "PartyPlayer.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "PartyGameModeBase.h"
#include "Physics/ImmediatePhysics/ImmediatePhysicsShared/ImmediatePhysicsCore.h"

// Sets default values
ADice::ADice()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	DiceComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DiceComp"));
	this->SetRootComponent(DiceComp);

	DicePoint1 = CreateDefaultSubobject<UBoxComponent>(TEXT("DicePoint1"));
	DicePoint2 = CreateDefaultSubobject<UBoxComponent>(TEXT("DicePoint2"));
	DicePoint3 = CreateDefaultSubobject<UBoxComponent>(TEXT("DicePoint3"));
	DicePoint4 = CreateDefaultSubobject<UBoxComponent>(TEXT("DicePoint4"));
	DicePoint5 = CreateDefaultSubobject<UBoxComponent>(TEXT("DicePoint5"));
	DicePoint6 = CreateDefaultSubobject<UBoxComponent>(TEXT("DicePoint6"));

	DicePoint1->SetupAttachment(RootComponent);
	DicePoint2->SetupAttachment(RootComponent);
	DicePoint3->SetupAttachment(RootComponent);
	DicePoint4->SetupAttachment(RootComponent);
	DicePoint5->SetupAttachment(RootComponent);
	DicePoint6->SetupAttachment(RootComponent);

	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));
	SceneCaptureComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADice::BeginPlay()
{
	Super::BeginPlay();
	DicePoint1->OnComponentBeginOverlap.AddDynamic(this, &ADice::OnDicePoint1BeginOverlap);
	DicePoint2->OnComponentBeginOverlap.AddDynamic(this, &ADice::OnDicePoint2BeginOverlap);
	DicePoint3->OnComponentBeginOverlap.AddDynamic(this, &ADice::OnDicePoint3BeginOverlap);
	DicePoint4->OnComponentBeginOverlap.AddDynamic(this, &ADice::OnDicePoint4BeginOverlap);
	DicePoint5->OnComponentBeginOverlap.AddDynamic(this, &ADice::OnDicePoint5BeginOverlap);
	DicePoint6->OnComponentBeginOverlap.AddDynamic(this, &ADice::OnDicePoint6BeginOverlap);

	GM = Cast<APartyGameModeBase>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void ADice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsRollingMode)
	{

		AddActorWorldRotation(FRotator(10, 10, 2));
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation.Z = RollingLocation.Z;
		SetActorLocation(CurrentLocation,true,nullptr,ETeleportType::TeleportPhysics);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Isrollingmode"));
	}


	if(IsStopRollingMode)
	{
		//미세한 위치 조정 필요
		SetActorLocation(StopRollingLocation, true, nullptr, ETeleportType::TeleportPhysics);
		
	}
}


void ADice::OnDicePoint1BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DiceNumber = 1;
	GM->CurrentPlayer->MoveRemaining = 1;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("1move"));
	AfterOverlap();
	
}

void ADice::OnDicePoint2BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DiceNumber = 2;
	GM->CurrentPlayer->MoveRemaining = 2;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("2move"));
	AfterOverlap();
}

void ADice::OnDicePoint3BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DiceNumber = 3;
	GM->CurrentPlayer->MoveRemaining = 3;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("3move"));
	AfterOverlap();
}

void ADice::OnDicePoint4BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DiceNumber = 4;
	GM->CurrentPlayer->MoveRemaining = 4;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("4move"));
	AfterOverlap();
}

void ADice::OnDicePoint5BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DiceNumber = 5;
	GM->CurrentPlayer->MoveRemaining = 5;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("5move"));
	AfterOverlap();
}

void ADice::OnDicePoint6BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DiceNumber = 6;
	GM->CurrentPlayer->MoveRemaining = 6;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("6move"));
	AfterOverlap();
}


void ADice::ThrowDice()
{
	
	DicePoint1->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DicePoint2->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DicePoint3->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DicePoint4->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DicePoint5->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DicePoint6->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DiceComp->SetSimulatePhysics(true);
	LaunchDice(1000);
}

void ADice::StartDiceRolling()
{
	IsRollingMode = true;
	RollingLocation = GetActorLocation();
}

void ADice::AfterOverlap()
{
	IsRollingMode = false;
	LaunchDice(200);
	StopRollingLocation = GetActorLocation();
	SetRotationToNumber(DiceNumber);


	DicePoint1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DicePoint2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DicePoint3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DicePoint4->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DicePoint5->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DicePoint6->SetCollisionEnabled(ECollisionEnabled::NoCollision);




	
}

void ADice::LaunchDice(float LaunchAmount)
{
	FVector LaunchDirection = FVector::UpVector; // 위쪽으로 띄우기 예시
	float LaunchStrength = LaunchAmount; // 띄우는 힘의 크기

	DiceComp->AddForce(LaunchDirection*LaunchStrength);

	//LaunchCharacter(LaunchDirection * LaunchStrength, true, true);
}

void ADice::SetRotationToNumber(int Number)
{

	switch (Number)
	{
	case 1:
	{
		SetActorRotation(FRotator(-90,0 ,0 ));
		break;
	}
	case 2:
	{
		SetActorRotation(FRotator(0,0 ,0 ));
		break;
	}
	case 3:
	{
		SetActorRotation(FRotator(-90,90 ,0 ));
		break;
	}
	case 4:
	{
		SetActorRotation(FRotator(-90, 90, 0));
		break;
	}
	case 5:
	{
		SetActorRotation(FRotator(-90, 90, 0));
		break;
	}
	case 6:
	{
		SetActorRotation(FRotator(-90, 90, 0));
		break;
	}


	}
}
