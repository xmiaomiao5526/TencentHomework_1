// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SuperPowerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEXTMENU_API USuperPowerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties

	USuperPowerComponent();

	//class TList<FVector> LocationList;
	TList<FVector>* HeaderPoint;

	TList<FVector>* LastPoint;

	class ACharacter* OwnerActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Loc")
	FVector FourSecondsBeforeLocation;

	FVector OwnerActoInitLoc;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Particle")
	//class UParticleSystemComponent* ParticleComp;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Particle")
	//class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Param")
	float CoolDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Param")
	float CoolTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Param")
	bool IsCoolDown;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void AddLocationToLast(FVector AddPos);

	void GetLocationFromHead();

	void TurnBackFourSecondsLoction();

	template<class MeshComponentType>
	void ShowFourSecondsAgoLoction(MeshComponentType* ShowMesh)
	{
		FVector NewLocation = FourSecondsBeforeLocation;
		NewLocation.Z -= 65;
		ShowMesh->SetWorldLocation(NewLocation);
	}
	 

};
/*
template <class ElementType> class TList
{
public:

	ElementType			Element;
	TList<ElementType>* Next;

	// Constructor.

	TList(const ElementType& InElement, TList<ElementType>* InNext = nullptr)
	{
		Element = InElement;
		Next = InNext;
	}
};*/
