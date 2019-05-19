// Copyright Martin Szabo

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

}

// Called every frame
void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent->GetAmmoLeft() > 0) { // TODO Find better way to handle AI tank running out of ammo

		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);

		// Aim towards player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked) {
			AimingComponent->Fire(); // TODO limit firing rate
		}
	}
}

