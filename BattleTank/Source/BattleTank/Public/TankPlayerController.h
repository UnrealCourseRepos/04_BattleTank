// Copyright Martin Szabo

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be last include


class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingCompRef);
private:
	
	// Start moving barrel so that a show would hit crosshair
	// crosshair intersects the world
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
	
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 100000;

	UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = 0.5;
	
	UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.33333;

	virtual void SetPawn(APawn * InPawn) override;

	UFUNCTION()
	void OnPossesedTankDeath();
};
