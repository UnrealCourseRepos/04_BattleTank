// Copyright Martin Szabo

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringStatus : uint8 {
	Reloading,
	Aiming,
	Locked
};

// Forward declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds barrel's properties and elevate method
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet);

	UFUNCTION(BlueprintCallable)
	void Fire();

private:

	// Sets default values for this component's properties
	UTankAimingComponent();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;
	
	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;
	
protected:

	// Asking to access this property from a sub class (TankAimingComponent in this case the parent is the c++ class)
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Aiming;
};