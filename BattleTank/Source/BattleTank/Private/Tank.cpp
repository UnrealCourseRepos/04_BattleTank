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

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BL BeginPlay() to run

	if (Health <= 0) {
		Health = DefaultHealth;
	}
}

/*void ATank::Destroyed()
{
	ExplosionBlast->Activate(); // TODO Add explosion blast to tank
}*/

float ATank::GetDefaultHealth()
{
	return DefaultHealth;
}

void ATank::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	if (Health <= 0) {

		UE_LOG(LogTemp, Warning, TEXT("Destroyed"))
		GetController()->GetPawn()->UnPossessed();
		Destroy();
	}

}

float ATank::GetHealth() {
	return Health;
}

float ATank::GetDamaged(float Damage) {

	Health = Health - Damage;
	return Health;
}

