// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Coin.generated.h"

/**
 * 
 */
UCLASS()
class TEXTMENU_API ACoin : public AItem
{
	GENERATED_BODY()
	ACoin();
	//UFUNCTION()
	virtual void PickUp(AActor* OtherActor) override;
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Value")
	float CoinValue;
};
