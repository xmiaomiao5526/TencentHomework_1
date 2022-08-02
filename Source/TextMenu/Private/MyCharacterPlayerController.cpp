// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterPlayerController.h"
#include "Blueprint/UserWidget.h"

AMyCharacterPlayerController::AMyCharacterPlayerController()
{
    TipsText = FText::FromString(" ");
}

void AMyCharacterPlayerController::BeginPlay()
{
    Super::BeginPlay();
    SetInputMode(FInputModeGameOnly());

    if (HUDAsset)
    {
        HUD = CreateWidget<UUserWidget>(this, HUDAsset);
        CurrentTipsWidgetWidget = CreateWidget<UUserWidget>(this, TipsWidgetClass);
    }
    if (HUD)
    {
        HUD->AddToViewport();
    }
}

void AMyCharacterPlayerController::ShowTips(FText TextForShow)
{
    TipsText = TextForShow;
    if (CurrentTipsWidgetWidget)
    {
		if (!CurrentTipsWidgetWidget->IsInViewport())
		{
			//CurrentTipsWidgetWidget->AddToPlayerScreen();
            CurrentTipsWidgetWidget->AddToViewport();
		}
    }
}

void AMyCharacterPlayerController::CloseTips()
{
    if (CurrentTipsWidgetWidget)
    {
		if (CurrentTipsWidgetWidget->IsInViewport())
		{
			CurrentTipsWidgetWidget->RemoveFromParent();
		}
    }
}