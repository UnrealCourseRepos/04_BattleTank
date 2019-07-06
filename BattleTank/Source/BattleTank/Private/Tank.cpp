// Copyright Martin Szabo

#include "Tank.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// TODO Add explosion blast to tank

}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	/* This function is second part of projectiles apply radial damage and gets
	called by it with: Projectile Damage Value, Projectile Location, Explosion Radius*/

	// Clamp the value between 0 and current health of the tank so we wont get negative health
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply; // Tank gets damaged
	
	// If Health equals 0 tank is destroyed
	if (CurrentHealth <= 0) {

		UE_LOG(LogTemp, Warning, TEXT("Destroyed"))
		GetController()->GetPawn()->UnPossessed();
		Destroy();
	}

	return DamageToApply;
	
}



// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BL BeginPlay() to run

	if (CurrentHealth <= 0) {
		CurrentHealth = StartingHealth;
	}
}

/*void ATank::Destroyed()
{
	ExplosionBlast->Activate(); // TODO Add explosion blast to tank
}*/

void ATank::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

float ATank::GetHealthPercentage() {
	return (float)CurrentHealth / (float)StartingHealth;
}
