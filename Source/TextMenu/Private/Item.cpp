// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "GameFramework/Actor.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(RootComponent);

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleComp");
	ParticleComp->SetupAttachment(RootComponent);

	IsRotate = false;
	RotationSpeed = 90;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlapBegin);
}

void AItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*
	 if (ParticleOverlap) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleOverlap, GetActorLocation());
	}
	*/
	if (OtherActor->GetClass()->IsChildOf(APawn::StaticClass()))
	{
		if (SoundOverlap) {
			UGameplayStatics::PlaySound2D(GetWorld(), SoundOverlap);
		}

		PickUp(OtherActor);
		Destroy();
	}

}

void AItem::PickUp(AActor* OtherActor)
{
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsRotate)
	{
		FRotator Rotation = MeshComp->GetComponentRotation();
		Rotation.Yaw += DeltaTime * RotationSpeed;
		MeshComp->SetWorldRotation(Rotation);
	}
}