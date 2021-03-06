// Copyright Martin Szabo

#include "TankBarrel.h"
#include "BattleTank.h"

void UTankBarrel::Elevate(float RelativeSpeed) {

	// Rotate barrel the right amount this frame
	// Given a max elevation speed, and frame time

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto ElevationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinDegreeElevation, MaxDegreeElevation);

	SetRelativeRotation(FRotator(Elevation, 0, 0));
	
	
}

