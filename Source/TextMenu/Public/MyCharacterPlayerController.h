// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyCharacterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEXTMENU_API AMyCharacterPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	//virtual void InitPlayerState();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> HUDAsset;
	UUserWidget* HUD;

	AMyCharacterPlayerController();

	UPROPERTY(BlueprintReadOnly)
	FText TipsText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<UUserWidget> TipsWidgetClass;
	class UUserWidget* CurrentTipsWidgetWidget;

	void ShowTips(FText TextForShow);

	void CloseTips();
};


