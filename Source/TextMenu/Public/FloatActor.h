// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatActor.generated.h"

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Sin,
	Rotate,
	Static
};

USTRUCT(BlueprintType)
struct FMovementParam
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = "Movement")
		float Amplitude = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
		EMovementType MoveType = EMovementType::Sin;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float Frequency = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float RotateSpeed = 90.0f;
};

UCLASS()
class TEXTMENU_API AFloatActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mash;

	UPROPERTY(EditAnywhere, Category = "Movement Paramaters")
	FMovementParam MovementParam;

	FVector InitialLocation;

	void HandleMovement(float DeltaTime);
};
