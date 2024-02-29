// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlueBoardSpace.generated.h"

UENUM(BlueprintType)
enum class ESpaceState : uint8
{
	Blue	UMETA(DisplayName = "Blue"),
	Red		UMETA(DisplayName = "Red"),
	Item	UMETA(DisplayName = "Item"),
	Trap	UMETA(DisplayName = "Trap"),
	Warp		UMETA(DisplayName = "Warp"),
	Star		UMETA(DisplayName = "Star"),
	TwoSideLoad		UMETA(DisplayName = "TwoSideLoad"),
};


UCLASS()
class SSACSTARS_API ABlueBoardSpace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlueBoardSpace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "YourCategory")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "YourCategory")
	UMaterialInterface* ItemMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "YourCategory")
	UMaterialInterface* BlueMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "YourCategory")
	UMaterialInterface* RedMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "YourCategory")
	UMaterialInterface* Material;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "YourCategory")
	UMaterialInterface* TrapMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "YourCategory")
	UMaterialInterface* WarpMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "YourCategory")
	UMaterialInterface* StarMaterial;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ESpaceState SpaceState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ABlueBoardSpace*>  NextSpace;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ABlueBoardSpace*>  PreviousSpace;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ABlueBoardSpace* WarpSpace;



public:
	void UpdateAppearance();

};

