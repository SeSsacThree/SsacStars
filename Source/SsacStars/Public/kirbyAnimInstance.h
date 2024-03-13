// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "kirbyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SSACSTARS_API UkirbyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed;

	UFUNCTION()
	void NativeUpdateAnimation(float DeltaSeconds) override;
};
