// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"


AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

		//Enables mobility for this actor even though it's static.
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

		//if this is server, then move.

	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		FVector GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

		FVector Direction = (GlobalTargetLocation - Location).GetSafeNormal();
		Location += MovementSpeed * DeltaTime * Direction;
		SetActorLocation(Location);
	}

}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

		//Enables replication to clients from server.

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

