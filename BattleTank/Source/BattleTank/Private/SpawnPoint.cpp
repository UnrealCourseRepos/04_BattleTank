// Copyright Martin Szabo


#include "SpawnPoint.h"
#include "Engine/World.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


AActor* USpawnPoint::GetSpawnedActor()
{
	return SpawnedActor;
}

// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	AActor* SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass,GetComponentTransform());

	if (!SpawnedActor) {
		UE_LOG(LogTemp, Warning, TEXT("CAT: Actor Not Spawned"));
		return;
	}

	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/*void USpawnPoint::Initialise(UClass * SpawnClassToSet) {
	SpawnClass = SpawnClassToSet;  // TODO Figure out when to call this
}*/
