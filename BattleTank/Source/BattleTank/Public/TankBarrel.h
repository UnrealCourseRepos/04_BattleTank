// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float DegreesPerSecond);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreePerSecond = 20; // Sensible Value

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreeElevation = 10; // Sensible Value

	UPROPERTY(EditAnywhere, Category = Setup)
		float MinDegreeElevation = -10; // Sensible Value
};
