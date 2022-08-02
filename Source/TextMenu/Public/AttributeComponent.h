// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEXTMENU_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeComponent();

protected:
	//当前关卡得分
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Attributes")
	float Score;
	//关卡目标
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float TargetScore;

	virtual void BeginPlay() override;
public:	

	UFUNCTION(BlueprintCallable,Category="Attributes")
	bool ApplyScoreChange(float Delta);

	//float GetCurrentTotalCoin() { return TotalCoin; }
	//void SetCurrentTotalCoin(float value) { TotalCoin = value; }

	float GetCurrentCoin() { return Score; }

	class AMainBaseGameMode* GM;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	FString LevelMesage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	FString TargetMesage;
};
