// Copyright Martin Szabo

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnPoint();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*UFUNCTION(BlueprintCallable, Category = "Setup")  // TODO Figure out when to call this
	void Initialise (UClass* SpawnClassToSet);*/

	AActor* GetSpawnedActor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// Config
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AActor> SpawnClass;

	AActor* SpawnedActor;
};
