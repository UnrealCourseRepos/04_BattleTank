// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Engine/World.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet) {

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {

	// No need to call super as we are replacing the functionality

	auto TankName = GetOwner()->GetName();
	auto MoveVelocityString = MoveVelocity.Normalize.ToString();
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp,Warning,TEXT("%f %s vectoring %s"), Time, *TankName, *MoveVelocityString)
}

void UTankMovementComponent::IntendMoveForward(float Throw) {

	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	//TODO prevent double speed due to double controll use

}

void UTankMovementComponent::IntendRotateClockwise(float Throw) {

	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	//TODO prevent double speed due to double controll use

}