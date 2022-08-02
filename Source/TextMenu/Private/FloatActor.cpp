// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFloatActor::AFloatActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mash = CreateDefaultSubobject<UStaticMeshComponent>("Mash");
	RootComponent = Mash;
}

// Called when the game starts or when spawned
void AFloatActor::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
}

// Called every frame
void AFloatActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleMovement(DeltaTime);
}

void AFloatActor::HandleMovement(float DeltaTime)
{
	switch (MovementParam.MoveType)
	{
	case EMovementType::Sin:
	{
		//z = z0 + Amplitude * sin(freq * t)
		FVector CurrentLocation = GetActorLocation();
		float Time = GetWorld()->GetTimeSeconds();
		CurrentLocation.Z = InitialLocation.Z + MovementParam.Amplitude * FMath::Sin(MovementParam.Frequency * Time);
		SetActorLocation(CurrentLocation);
	}break;
	case EMovementType::Rotate:
	{
		FRotator Rotation = Mash->GetComponentRotation();
		Rotation.Yaw += DeltaTime * MovementParam.RotateSpeed;
		Mash->SetWorldRotation(Rotation);
	}
	case EMovementType::Static:break;
	default:break;
	}
}