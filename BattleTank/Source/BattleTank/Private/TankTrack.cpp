// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "BattleTank.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	// Calculate the slippage speed
	// Work-out the required acceleration this frame to correct
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(),GetComponentVelocity());
	auto CorrectionAcceleration = - SlippageSpeed / DeltaTime * GetRightVector();

	// Calculate and apply sideways force (F = m * a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass()* CorrectionAcceleration) / 2;  //Two Tracks
	TankRoot->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle) {
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied,ForceLocation);
}