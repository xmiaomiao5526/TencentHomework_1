// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class TEXTMENU_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USuperPowerComponent* SuperPowerComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ShadowMesh")
	class UStaticMeshComponent* MeshComp;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ShadowMesh")
	//class USkeletalMeshComponent* SkeletalMeshComp;

protected:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComp;

	//UPROPERTY(VisibleAnywhere)
	//class UInteractionComponent* InteractionComp;

	float BaseTurnRate;

	float BaseLookupRate;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Value);

	void TurnLookupRate(float Value);

	//void PrimaryInteract();

	void BackInTime();

	void ReloadGame();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
	//UFUNCTION(BlueprintCallable)
	//void SaveGame();

	//UFUNCTION(BlueprintCallable)
	//void LoadGame();

};
