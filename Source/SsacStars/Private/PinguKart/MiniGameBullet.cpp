// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGameBullet.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h"
#include "KartPlayer.h"

// Sets default values
AMiniGameBullet::AMiniGameBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	
	SetRootComponent(boxComp);
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);

	boxComp->SetGenerateOverlapEvents( true );
	boxComp->SetCollisionProfileName(TEXT("Bullet"));
	
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AMiniGameBullet::BeginPlay()
{
	Super::BeginPlay();
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AMiniGameBullet::OnMyCompBeginOverlap);
}

// Called every frame
void AMiniGameBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector dir = GetActorForwardVector();
	FVector P0 = GetActorLocation();
	FVector vt = dir * speed * GetWorld()->GetDeltaSeconds();
	SetActorLocation(P0 + vt);
}

void AMiniGameBullet::OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AKartPlayer* OverlapPlayer = Cast<AKartPlayer>( OtherActor )) {

		if (!OverlapPlayer->GetController())
		{
			UE_LOG( LogTemp , Warning , TEXT( "!OverlapPlayer->GetController()" ) );
			return;
		}
		
		//부딪힌 플레이어가 로컬 플레이어가 아니라면
		if (OverlapPlayer->GetController() && !OverlapPlayer->GetController()->IsLocalPlayerController())
		{
			UE_LOG( LogTemp , Warning , TEXT( "!OverlapPlayer->GetController()->IsLocalPlayerController()" ) );
			OverlapPlayer->ServerSetStarCount(-1);
		}
		//서버 destroy
		/*FTimerHandle DelayTimerHandle;
		GetWorld()->GetTimerManager().SetTimer( DelayTimerHandle , FTimerDelegate::CreateLambda(
			[this]()->void
			{
				Destroy();
			}
		) , 10 , false );*/
		
	}
}

