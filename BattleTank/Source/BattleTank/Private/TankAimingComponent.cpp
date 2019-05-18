// Copyright Martin Szabo

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankAimingComponent::BeginPlay()
{
	// So that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if(Ammo <= 0) {
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringStatus = EFiringStatus::Aiming;
	}
	else {
		FiringStatus = EFiringStatus::Locked;
	}
	
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}

int UTankAimingComponent::GetAmmoLeft() const
{
	return Ammo;
}

int UTankAimingComponent::GetAmmoAtBeginPlay() const
{
	return AmmoAtBeginPlay;
}

void UTankAimingComponent::Initialise(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet)
{

	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{

	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		TArray < AActor *  >(),
		false // Debug Line (RayCasting)
	);

	

	if (bHaveAimSolution) {
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	
	// No aim solution found
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	
	if (!ensure(Barrel && Turret)) { return; }

	// Workout the diffrence between current barrel rotation and Aim Direction
	auto TankName = GetOwner()->GetName();
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	// Always yaw the shortest way
	Barrel->Elevate(DeltaRotator.GetNormalized().Pitch);
	if (FMath::Abs(DeltaRotator.GetNormalized().Yaw) > 180) {
		Turret->Rotate(-DeltaRotator.GetNormalized().Yaw);
	}
	else { // Avoid going the long way
		Turret->Rotate(DeltaRotator.GetNormalized().Yaw);
	}
	

	// so it will point at cordinates of where the player is looking over few frames
	// Report back the rotation state of the 
	// the corditantes of the hit and MAYBE if it hit any enemy tank

}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01); //Vectors are equal
}

void UTankAimingComponent::Fire() {

	if (FiringStatus == EFiringStatus::Locked || FiringStatus == EFiringStatus::Aiming) {

		// Spawn projectile at the socket location
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

			Projectile->LaunchProjectile(LaunchSpeed);
			LastFireTime = FPlatformTime::Seconds();
			Ammo--;
	}
}


