// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeComponent.h"
#include "MainBaseGameMode.h"

// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	Score = 0;
	LevelMesage = "Level: ";
	TargetMesage = "TargetScore: ";
}


void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();



	GM = GetWorld()->GetAuthGameMode<AMainBaseGameMode>();
	if (GM)
	{
		FString WholeLevelName = GetWorld()->GetMapName();
		LevelMesage ="Level: "+ WholeLevelName.Right(1);
		TargetScore = GM->GetDefaultTargetScore();
		TargetMesage = "TargetScore: " + FString::FromInt(TargetScore);
	}
	
}

bool UAttributeComponent::ApplyScoreChange(float Delta)
{
	Score += Delta;
	return true;
}