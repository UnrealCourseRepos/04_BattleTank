// Copyright Martin Szabo

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declarations


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	
	//...
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetDamaged(float Damage);

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetDefaultHealth();

	virtual void Tick(float DeltaTime) override;

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

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float DefaultHealth = 3000;

	float Health;
};
