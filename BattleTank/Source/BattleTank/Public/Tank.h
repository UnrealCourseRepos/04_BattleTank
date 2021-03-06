// Copyright Martin Szabo

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Delegate.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	
	//...

	// TODO make health bar widget turn red at 25% or less only for the that has 25% or less health (Inside HealthBar blueprint in Get_ProgressBar_FillAndOpacity)

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercentage();

	virtual void Tick(float DeltaTime) override;

	FTankDelegate OnDeath;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// virtual void Destroyed(); // TODO Add explosion blast to tank

private:
	// Sets default values for this pawn's properties
	ATank();

	// TODO Add explosion blast to tank
	/*UPROPERTY(VisibleAnywhere, Category = "Components", meta=(AllowPrivateAccess = "true"))
	UParticleSystemComponent * ExplosionBlast = nullptr;*/

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 StartingHealth = 3000;

	int32 DamageToApply;

	int32 CurrentHealth;
};
