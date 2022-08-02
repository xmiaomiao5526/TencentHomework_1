// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class TEXTMENU_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Item|Collision")
	class USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item|Mash")
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item|Particle")
	class UParticleSystemComponent* ParticleComp;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item|Particle")
	//UParticleSystemComponent* ParticleOverlap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Sound")
	class USoundCue* SoundOverlap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Movement")
	bool IsRotate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Movement")
	float RotationSpeed;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void PickUp(AActor* OtherActor);

	void SetIsRotateDefault(bool NewValue) { IsRotate = NewValue; }
	void SetRotateSpeedDefault(float NewValue) { RotationSpeed = NewValue; }
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
