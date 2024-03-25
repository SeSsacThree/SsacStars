// Fill out your copyright notice in the Description page of Project Settings.


#include "RollDiceCharacter.h"
#include "PartyGameStateBase.h"
#include "RollDiceCharacter.h"
#include "Dice.h"
#include "PartyPlayer.h"
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



	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>( TEXT( "SceneCaptureComponent" ) );
	this->SetRootComponent( SceneCaptureComponent );


	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>( TEXT( "MeshComp" ) );
	MeshComp->SetupAttachment( SceneCaptureComponent );

	handComp = CreateDefaultSubobject<USceneComponent>( TEXT( "handComp" ) );
	handComp->SetupAttachment( SceneCaptureComponent );



}

// Called when the game starts or when spawned
void ARollDiceCharacter::BeginPlay()
{
	Super::BeginPlay();
	Dice = Cast<ADice>( UGameplayStatics::GetActorOfClass( GetWorld() , ADice::StaticClass() ) );
	//ThrowDiceUi = NewObject<UThrowDiceCharacterUi>( this , ThrowDiceUiFactory );
	PartyGameState=Cast<APartyGameStateBase>( GetWorld()->GetGameState() );
	//if(HasAuthority())
		//ServerCreateDice();
	//CreateDice();
	//ServerGrabDice( Dice );
	BeginLocation = GetActorLocation();

	SceneCaptureComponent->ShowOnlyActorComponents( this,true );
}

// Called every frame
void ARollDiceCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	//SetActorLocation( FVector( BeginLocation.X , BeginLocation.Y , GetActorLocation().Z ) );
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
		GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Red , TEXT( "Dice" ) );
		//GrapDice(Dice);
		ServerGrabDice( Dice );
	}


}
void ARollDiceCharacter::ServerCreateDice_Implementation()
{
	/*
	if (Dice)
	{
		GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Red , TEXT( "Dice" ) );
		//GrapDice(Dice);
		ServerGrabDice( Dice );
	}
	*/
	Dice->ReBack();
	Dice->IsStopRollingMode = false;
	auto mesh = Dice->GetComponentByClass<USkeletalMeshComponent>();
	//mesh->SetSimulatePhysics(false);
	//mesh->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	mesh->AttachToComponent( handComp , FAttachmentTransformRules::SnapToTargetNotIncludingScale );
	GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Red , TEXT( "GrabDice" ) );
	Dice->SetOwner( this );
	//MultiCreateDice();
}

void ARollDiceCharacter::MultiCreateDice_Implementation()
{


	/*
	TArray<struct FOverlapResult> OutOverlaps;
	FCollisio	bjectQueryParams ObjectQueryParams(FCollisionObjectQueryParams::InitType::AllObjects);
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



}

void ARollDiceCharacter::ThrowDice( const AActor* Actor )
{
	
	if (nullptr == Actor)
		return;
	//Dice->SetActorEnableCollision(false);

	auto mesh = Actor->GetComponentByClass<USkeletalMeshComponent>();
	// pistol 물리를 켜고싶다.
	//mesh->SetSimulatePhysics(true);
	//mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	//mesh->SetCollisionResponseToAllChannels(ECR_Block);
	// hand에서 떼고싶다.
	mesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Throw"));
	Dice->SetOwner( nullptr );

}
void ARollDiceCharacter::ServerThrowDice_Implementation( const AActor* Actor )
{
	//UE_LOG( LogTemp , Warning , TEXT( " ARollDiceCharacter::ServerThrowDice_Implementation(" ) );
	MultiThrowDice( Actor );
}

void ARollDiceCharacter::MultiThrowDice_Implementation( const AActor* Actor )
{
	if (nullptr == Actor)
		return;
	//Dice->SetActorEnableCollision(false);

	auto mesh = Actor->GetComponentByClass<USkeletalMeshComponent>();
	// pistol 물리를 켜고싶다.
	//mesh->SetSimulatePhysics(true);
	//mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//mesh->SetCollisionResponseToAllChannels(ECR_Block);
	// hand에서 떼고싶다.
	mesh->DetachFromComponent( FDetachmentTransformRules::KeepWorldTransform );
	GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Red , TEXT( "Throw" ) );
	UE_LOG( LogTemp , Warning , TEXT( " ARollDiceCharacter::MultiThrowDice_Implementation(" ) );

	//Dice->SetOwner( nullptr );
}

void ARollDiceCharacter::GrapDice( const AActor* Actor )
{
	
	Dice->ReBack();
	Dice->IsStopRollingMode = false;
	auto mesh = Actor->GetComponentByClass<USkeletalMeshComponent>();
	//mesh->SetSimulatePhysics(false);
	mesh->AttachToComponent(handComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GrabDice"));
	Dice->SetOwner( this );
}

void ARollDiceCharacter::ServerGrabDice_Implementation( const AActor* Actor )
{
	MultiGrabDice( Actor );
}

void ARollDiceCharacter::MultiGrabDice_Implementation( const AActor* Actor )
{
	Dice->ReBack();
	Dice->IsStopRollingMode = false;
	auto mesh = Actor->GetComponentByClass<USkeletalMeshComponent>();
	//mesh->SetSimulatePhysics(false);
	//mesh->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	mesh->AttachToComponent( handComp , FAttachmentTransformRules::SnapToTargetNotIncludingScale );
	GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Red , TEXT( "GrabDice" ) );
	Dice->SetOwner( this );
}
void ARollDiceCharacter::GetSignal()
{
	UE_LOG( LogTemp , Warning , TEXT( " ARollDiceCharacter::GetSignal(" ) );
	//ServerThrowDice( Dice );
	//ThrowDice(Dice);
	Dice->ThrowDice();
	//Dice->ServerThrowDice();
	//Dice->IsUpMode = true;
}

void ARollDiceCharacter::StartRolling()
{
	Dice->StartDiceRolling();
	//Dice->ServerStartDiceRolling();
	if(HasAuthority())
		UE_LOG( LogTemp , Warning , TEXT( "RemainStartRolling" ) );
}

void ARollDiceCharacter::AddView()
{
	/*
	if (ThrowDiceUi)
		ThrowDiceUi->AddToViewport();
		*/
}

void ARollDiceCharacter::CloseView()
{




	DelayTime( 1.0f , [this]()
		{
			//변환필요
			//ServerGrabDice( Dice );
			//GrapDice(Dice);
			//ServerRemoveThrowDiceUi();
			PartyGameState->ServerRemoveThrowDiceUi();
			//ThrowDiceUi->RemoveFromParent();

		} );

}

void ARollDiceCharacter::Jump( float LaunchAmount )
{
	FVector LaunchDirection = FVector::UpVector; // 위쪽으로 띄우기 예시
	float LaunchStrength = LaunchAmount; // 띄우는 힘의 크기


}

void ARollDiceCharacter::DelayTime( float WantSeconds , TFunction<void()> InFunction )
{

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer( TimerHandle , [InFunction]()
		{
			// 지연 후 실행될 함수 호출
			InFunction();
		} , WantSeconds , false );
}



void ARollDiceCharacter::ServerRemoveThrowDiceUi_Implementation()
{
	
	//MultiRemoveThrowDiceUi();
	
}

void ARollDiceCharacter::MultiRemoveThrowDiceUi_Implementation()
{
	/*
	if(ThrowDiceUi)
	{
		ThrowDiceUi->RemoveFromParent();

	}
	*/
}

void ARollDiceCharacter::ServerViewThrowDiceUi_Implementation()
{
	MultiViewThrowDiceUi();
}

void ARollDiceCharacter::MultiViewThrowDiceUi_Implementation()
{
	/*
	if (ThrowDiceUi)
	{
		ThrowDiceUi->AddToViewport();
	}
	*/
}




void ARollDiceCharacter::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
	DOREPLIFETIME( ARollDiceCharacter , Dice );
	//DOREPLIFETIME( ARollDiceCharacter , handComp );
	
}
