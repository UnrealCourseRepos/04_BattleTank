// Copyright Martin Szabo

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"


/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max downward speed and +1 is max up movement
	void Rotate(float RelativeSpeed);

private:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreePerSecond = 10; // Sensible Value

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreeRotation = 180; // Sensible Value

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinDegreeRotation = -180; // Sensible Value

	
};
