// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainBaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TEXTMENU_API AMainBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMainBaseGameMode();

	FString SlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Win")
	FName NextLevelName;

	//UPROPERTY()
	//class FName SavedLevelName;

	UPROPERTY()
	class UMySaveGame* CurrentSaveGame;

	class UMySaveGame* MyInstance;

	UFUNCTION(BlueprintCallable,Category="SaveGame")
	void SaveGame();

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void InitializeGame();

	UFUNCTION(BlueprintCallable, Category = "LoadMyGame")
	void LoadGame();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Win")
	float TargetScore;

	void SetDefaultTargetScore(float Value) { TargetScore = Value; }
	float GetDefaultTargetScore() { return TargetScore; }

	//void AddTotalCoin(float value) { TotalCoin += value; }
	//float GetTotalCoin() { return TotalCoin; }

	class AMyCharacter* MyCharacter;

	virtual void StartPlay() override;

	bool IsGoToNextLevel(class AMyCharacter *MyCharacter);
};