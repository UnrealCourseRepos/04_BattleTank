// Copyright Martin Szabo

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed and +1 is max up movement
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxDegreePerSecond = 5; // Sensible Value

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxDegreeElevation = 20; // Sensible Value

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MinDegreeElevation = 0; // Sensible Value

};
