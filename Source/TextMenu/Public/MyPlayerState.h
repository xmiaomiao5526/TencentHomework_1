// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
class UMySaveGame;
UCLASS()
class TEXTMENU_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
	AMyPlayerState();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TotalCoin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NextLevelName;

	UFUNCTION(BlueprintNativeEvent)
	void SavePlayState(UMySaveGame* SaveObject);

	UFUNCTION(BlueprintNativeEvent)
	void LoadPlayState(UMySaveGame* SaveObject);

	void SetTotalCoin(float value) { TotalCoin += value; }
	float GetTotalCoin() { return TotalCoin; }

	void CopyProperties(APlayerState* PlayerState) override;
};
