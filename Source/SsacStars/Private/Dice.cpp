// Fill out your copyright notice in the Description page of Project Settings.


#include "Dice.h"
#include "Components/SceneCaptureComponent2D.h"
#include "PartyPlayer.h"
#include "Components/BoxComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "PartyGameModeBase.h"


// Sets default values
ADice::ADice()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

	SceneCaptureDice = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureDice"));
	this->SetRootComponent(SceneCaptureDice);
	

	DiceComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DiceComp"));

	DiceComp->SetupAttachment(SceneCaptureDice);
	

	DiceComp->SetSimulatePhysics(false);
	//DiceComp->SetSimulatePhysics(true);
	DicePoint1 = CreateDefaultSubobject<UBoxComponent>(TEXT("DicePoint1"));
	DicePoint2 = CreateDefaultSubobject<UBoxComponent>(TEXT("DicePoint2"));
	DicePoint3 = CreateDefaultSubobject<UBoxComponent>(TEXT("DicePoint3"));
	DicePoint4 = CreateDefaultSubobject<UBoxComponent>(TEXT("DicePoint4"));
	DicePoint5 = CreateDefaultSubobject<UBoxComponent>(TEXT("DicePoint5"));
	DicePoint6 = CreateDefaultSubobject<UBoxComponent>(TEXT("DicePoint6"));

	DicePoint1->SetupAttachment(DiceComp);
	DicePoint2->SetupAttachment(DiceComp);
	DicePoint3->SetupAttachment(DiceComp);
	DicePoint4->SetupAttachment(DiceComp);
	DicePoint5->SetupAttachment(DiceComp);
	DicePoint6->SetupAttachment(DiceComp);


	DicePoint1->SetCollisionProfileName("Pawn");
	DicePoint2->SetCollisionProfileName("Pawn");
	DicePoint3->SetCollisionProfileName("Pawn");
	DicePoint4->SetCollisionProfileName("Pawn");
	DicePoint5->SetCollisionProfileName("Pawn");
	DicePoint6->SetCollisionProfileName("Pawn");


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

	BeginLocation = DiceComp->GetComponentLocation();
}

// Called every frame
void ADice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	//SceneCaptureDice->ShowOnlyActorComponents(this);

	DiceComp->SetWorldLocation(FVector(BeginLocation.X, BeginLocation.Y, DiceComp->GetComponentLocation().Z));

	if(IsUpMode)
	{
		
		FVector CurrentLocation = DiceComp->GetComponentLocation() +DiceComp->GetUpVector() * 160.0f * GetWorld()->GetDeltaSeconds();
		DiceComp->SetWorldLocation(CurrentLocation);
		
		FVector CurrentScale = DiceComp->GetComponentScale();
		FVector ScaleToAddVector = FVector(0.07);
		FVector NewScale = CurrentScale + ScaleToAddVector;
		DiceComp->SetWorldScale3D(NewScale);
	}


	if (IsRollingMode)
	{
		DiceComp->AddWorldRotation(FRotator(10, 10, 10));
		FVector CurrentLocation = DiceComp->GetComponentLocation();
		CurrentLocation.Z = RollingLocation.Z;
		DiceComp->SetWorldLocation(CurrentLocation,true,nullptr,ETeleportType::TeleportPhysics);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Isrollingmode"));
	}


	if(IsStopRollingMode)
	{
		//미세한 위치 조정 필요
		DiceComp->SetWorldLocation(StopRollingLocation, false, nullptr, ETeleportType::TeleportPhysics);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NeedStop"));
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
	//DiceComp->SetSimulatePhysics(true);
	IsUpMode = true;
	//LaunchDice(1000000);
}

void ADice::StartDiceRolling()
{
	IsUpMode = false;
	IsRollingMode = true;
	RollingLocation = DiceComp->GetComponentLocation();
}

void ADice::AfterOverlap()
{
	DicePoint1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DicePoint2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DicePoint3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DicePoint4->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DicePoint5->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DicePoint6->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DiceComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	
	//LaunchDice(200);
	StopRollingLocation = DiceComp->GetComponentLocation();
	IsRollingMode = false;
	IsStopRollingMode = true;
	IsSelected = true;
	SetRotationToNumber(DiceNumber);


	GM->CurrentPlayer->ItemApply();




	
}

void ADice::LaunchDice(float LaunchAmount)
{
	FVector LaunchDirection = FVector::UpVector; // 위쪽으로 띄우기 예시
	float LaunchStrength = LaunchAmount; // 띄우는 힘의 크기
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Addforce"));
	DiceComp->AddForce(LaunchDirection*LaunchStrength);

	//LaunchCharacter(LaunchDirection * LaunchStrength, true, true);
}

void ADice::SetRotationToNumber(int Number)
{

	switch (Number)
	{
	case 1:
	{
		DiceComp->SetRelativeLocationAndRotation(FVector(16.666667,0 , -8.333333), FRotator(0,0 ,90 ));
		
		break;
	}
	case 2:
	{
		DiceComp->SetRelativeLocationAndRotation(FVector(25, 0, -8.333333), FRotator(-90, 0, 270));
		break;
	}
	case 3:
	{
		DiceComp->SetRelativeLocationAndRotation(FVector(( 16.666667, -8.333333,  0.000000)), FRotator(-90, 0, 180));
		break;
	}
	case 4:
	{
		DiceComp->SetRelativeLocationAndRotation(FVector((16.666666, 8.333333,  0.000000)), FRotator(-90, 0, 0));
		break;
	}
	case 5:
	{
		DiceComp->SetRelativeLocationAndRotation(FVector(( 8.333333,  -0.000000, 0.000000)), FRotator(-90, 0, 90));
		break;
	}
	case 6:
	{
		DiceComp->SetRelativeLocationAndRotation(FVector(( 15.000000,  -0.000000,  8.333334)), FRotator(-180, 0, 90));
		break;
	}


	}
}

void ADice::ReBack()
{
	 IsRollingMode = false;
	 IsStopRollingMode = false;
	 IsUpMode = false;
	 DiceComp->SetWorldLocation(BeginLocation);
	 DiceComp->SetWorldScale3D(FVector(0.1f));

	 GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ReBack"));
}
