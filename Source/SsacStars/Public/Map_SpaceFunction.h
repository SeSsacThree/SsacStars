// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "Map_SpaceFunction.generated.h"

UCLASS()
class SSACSTARS_API AMap_SpaceFunction : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMap_SpaceFunction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void TeleportActor(AActor* ActorToTeleport);

	UPROPERTY(EditAnywhere)
	FVector TeleportDestination;

	void PlusThreeSpaces();

};
