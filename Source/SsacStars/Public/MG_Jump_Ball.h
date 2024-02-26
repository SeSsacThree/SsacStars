// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MG_Jump_Ball.generated.h"

UCLASS()
class SSACSTARS_API AMG_Jump_Ball : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMG_Jump_Ball();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	float moveSpeed = 300.0f;


	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;

	UPROPERTY()
	class UStaticMeshComponent* meshComp;

	void MoveBallRight();
	void MoveBallLeft();

private:
	FVector dir;
};
