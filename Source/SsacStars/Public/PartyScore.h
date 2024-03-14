// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PartyScore.generated.h"

UCLASS()
class SSACSTARS_API APartyScore : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APartyScore();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* ScoreComp;

	UPROPERTY(EditAnywhere)
	class ABlueBoardSpace* StarSpace;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;
public:
	UFUNCTION()
	void ReSpace();
	UFUNCTION()
	void GetCamera();


};
