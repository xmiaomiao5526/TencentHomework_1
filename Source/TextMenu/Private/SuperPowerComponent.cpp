// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperPowerComponent.h"
#include "Containers/List.h"
#include "Math/Vector.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MyCharacterPlayerController.h"

// Sets default values for this component's properties
USuperPowerComponent::USuperPowerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	HeaderPoint = new TList<FVector>(FVector::ZeroVector,nullptr);
	LastPoint = HeaderPoint;
	CoolDown = 4;
	CoolTimer = 0;

	//ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("ShadowParticle");

	// ...
}


// Called when the game starts
void USuperPowerComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerActor = GetOwner<ACharacter>();
	OwnerActoInitLoc = OwnerActor->GetActorLocation();
	FourSecondsBeforeLocation = OwnerActoInitLoc;
}


// Called every frame
void USuperPowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AddLocationToLast(OwnerActor->GetActorLocation());
	if (GetWorld()->GetTimeSeconds()>4)
	{
		GetLocationFromHead();
	}
	//MeshComp->SetWorldLocation(FourSecondsBeforeLoction);
	if (CoolTimer < CoolDown)
	{
		CoolTimer += DeltaTime;
		IsCoolDown = false;
	}
	else
	{
		IsCoolDown = true;
	}
	UE_LOG(LogTemp, Error, TEXT("CD:%.2f,"), CoolTimer)
/*
	UE_LOG(LogTemp, Error, TEXT("HeaderPoint->Next =(%.2f,,%.2f,,%.2f)"), HeaderPoint->Next->Element.X, HeaderPoint->Next->Element.Y, HeaderPoint->Next->Element.Z)
	UE_LOG(LogTemp, Error, TEXT("Current Location =(%.2f,,%.2f,,%.2f)"), OwnerActor->GetActorLocation().X, OwnerActor->GetActorLocation().Y, OwnerActor->GetActorLocation().Z)
	UE_LOG(LogTemp, Error, TEXT("Game Time:%.2f,My Location =(%.2f,,%.2f,,%.2f)"), GetWorld()->GetTimeSeconds(), FourSecondsBeforeLoction.X, FourSecondsBeforeLoction.Y, FourSecondsBeforeLoction.Z)
*/
	// ...
}

void USuperPowerComponent::AddLocationToLast(FVector AddPos)
{
	TList<FVector>* AddNode = new TList<FVector>(AddPos, nullptr);
	LastPoint->Next = AddNode;
	LastPoint = LastPoint->Next;
}

void USuperPowerComponent::GetLocationFromHead()
{
	TList<FVector>* ResNode = HeaderPoint->Next;
	FourSecondsBeforeLocation = FVector(ResNode->Element.X, ResNode->Element.Y, ResNode->Element.Z);
	HeaderPoint->Next = ResNode->Next;
	delete(ResNode);
}

void USuperPowerComponent::TurnBackFourSecondsLoction()
{
	if (IsCoolDown)
	{
		CoolTimer = 0;
		GetOwner()->SetActorLocation(FourSecondsBeforeLocation);
	}
}

