// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyScore.h"
#include "Camera/CameraComponent.h"
#include "BlueBoardSpace.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
// Sets default values
APartyScore::APartyScore()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ScoreComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ScoreComp"));
	this->SetRootComponent(ScoreComp);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(ScoreComp); // RootComponent에 카메라를 붙이거나 원하는 다른 컴포넌트에 붙일 수 있습니다.
}

// Called when the game starts or when spawned
void APartyScore::BeginPlay()
{
	Super::BeginPlay();

	ReSpace();

}

// Called every frame
void APartyScore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

			if (StarSpace)
			{
				FVector StarLocation = StarSpace->GetActorLocation();
				
				StarLocation.Z += OscillatingValue(450.0f, 650.0f, 0.01f);
				PlayerLocation = StarLocation;
				SetActorLocation(PlayerLocation, false, nullptr, ETeleportType::TeleportPhysics);
			}

			
}

void APartyScore::ReSpace()
{


	//맵의 모든 발판을 가져와서 
	for (TActorIterator<ABlueBoardSpace> It(GetWorld()); It; ++It)
	{
		// space에 저장해서 
		ABlueBoardSpace* Space = *It;
		//가져온 발판의 상태가 Star 라면 
		if (Space->SpaceState == ESpaceState::Star)
		{
			//Starspace 변수에 집어넣는다
			StarSpace = Space;
		}

	}

}

void APartyScore::GetCamera()
{
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	OurPlayerController->SetViewTargetWithBlend(this, 1.0f);
}

float APartyScore::OscillatingValue(float min, float max, float speed)
{
	static float currentTime = 0.0f;
	currentTime += speed;

	float oscillation = (sinf(currentTime) + 1.0f) / 2.0f; // 사인 함수 값을 0부터 1로 매핑

	return min + oscillation * (max - min); // min과 max 사이의 값으로 변환
}

void APartyScore::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(APartyScore, PlayerLocation, COND_OwnerOnly);
}

