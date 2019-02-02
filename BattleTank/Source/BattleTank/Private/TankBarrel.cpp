// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "BattleTank.h"

void UTankBarrel::Elevate(float DegreesPerSecond) {

	UE_LOG(LogTemp, Warning, TEXT("Barrel->Elevate() called at speed %f"), DegreesPerSecond);

	// Rotate barrel the right amount this frame
	// Given a max elevation speed, and frame time
}