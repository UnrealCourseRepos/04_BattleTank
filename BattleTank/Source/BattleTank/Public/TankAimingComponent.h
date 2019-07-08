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
	Locked,
	OutOfAmmo
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

	bool IsBarrelMoving();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet, UClass * ProjectileBlueprintToSet);

	UFUNCTION(BlueprintCallable)
	void Fire();

	EFiringStatus GetFiringStatus() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetAmmoLeft() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetAmmoAtBeginPlay() const;


private:

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

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

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 Ammo = 15;

	const int32 AmmoAtBeginPlay = Ammo;

	FVector AimDirection;


protected:

	// Asking to access this property from a sub class (TankAimingComponent in this case the parent is the C++ class)
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

};