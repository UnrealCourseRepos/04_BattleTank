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

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float DefaultHealth = 3000;

	float Health;
};
