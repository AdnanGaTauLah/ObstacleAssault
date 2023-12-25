// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
//send platform back to start when moved too far 
	// check how far we've moved
	// if we've moved too far, reverse direction
	if (ShouldPlatformReturn())
	{
		// get direction of movement
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		// set new start location
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		// set new location
		SetActorLocation(StartLocation);
		// reverse direction
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
	// continue moving

// move platform forward 
	// get current location
	FVector CurrentLocation = GetActorLocation();
	// add vector to current location
	CurrentLocation = CurrentLocation + PlatformVelocity * DeltaTime;
	// set new location
	SetActorLocation(CurrentLocation);

	}
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}