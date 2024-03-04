// Fill out your copyright notice in the Description page of Project Settings.


#include "Dice.h"

#include "PartyPlayer.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
// Sets default values
ADice::ADice()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	DiceMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DiceMesh"));
	this->SetRootComponent(DiceMesh);

	DicePoint1 = CreateDefaultSubobject<UBoxComponent>(TEXT("DicePoint1"));
	DicePoint2 = CreateDefaultSubobject<UBoxComponent>(TEXT("DicePoint2"));
	DicePoint3 = CreateDefaultSubobject<UBoxComponent>(TEXT("DicePoint3"));
	DicePoint4 = CreateDefaultSubobject<UBoxComponent>(TEXT("DicePoint4"));
	DicePoint5 = CreateDefaultSubobject<UBoxComponent>(TEXT("DicePoint5"));
	DicePoint6 = CreateDefaultSubobject<UBoxComponent>(TEXT("DicePoint6"));

	DicePoint1->SetupAttachment(DiceMesh);
	DicePoint2->SetupAttachment(DiceMesh);
	DicePoint3->SetupAttachment(DiceMesh);
	DicePoint4->SetupAttachment(DiceMesh);
	DicePoint5->SetupAttachment(DiceMesh);
	DicePoint6->SetupAttachment(DiceMesh);

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
		SetActorLocation(CurrentLocation);
	}


	if(IsStopRollingMode)
	{
		//미세한 위치 조정 필요 
		SetActorLocation(StopRollingLocation);
	}
}

// Called to bind functionality to input
void ADice::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADice::OnDicePoint1BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GM->CurrentPlayer->MoveRemaining = 1;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("1move"));
	AfterOverlap();

}

void ADice::OnDicePoint2BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GM->CurrentPlayer->MoveRemaining = 2;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("2move"));
	AfterOverlap();
}

void ADice::OnDicePoint3BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GM->CurrentPlayer->MoveRemaining = 3;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("3move"));
	AfterOverlap();
}

void ADice::OnDicePoint4BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GM->CurrentPlayer->MoveRemaining = 4;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("4move"));
	AfterOverlap();
}

void ADice::OnDicePoint5BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GM->CurrentPlayer->MoveRemaining = 5;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("5move"));
	AfterOverlap();
}

void ADice::OnDicePoint6BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GM->CurrentPlayer->MoveRemaining = 6;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("6move"));
	AfterOverlap();
}


void ADice::ThrowDice()
{
	DiceMesh->SetSimulatePhysics(true);
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
}

void ADice::LaunchDice(float LaunchAmount)
{
	FVector LaunchDirection = FVector::UpVector; // 위쪽으로 띄우기 예시
	float LaunchStrength = LaunchAmount; // 띄우는 힘의 크기

	LaunchCharacter(LaunchDirection * LaunchStrength, false, false);
}
