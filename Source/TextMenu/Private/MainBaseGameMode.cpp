// Fill out your copyright notice in the Description page of Project Settings.


#include "MainBaseGameMode.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SaveGame.h"
#include "Logging/LogMacros.h"
#include "EngineUtils.h"
#include "MySaveGame.h"
#include "GameFramework/GameModeBase.h"
#include "MyPlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "AttributeComponent.h"

AMainBaseGameMode::AMainBaseGameMode()
{
	TargetScore = 5;
	SlotName = TEXT("MySaveGame");
	NextLevelName = "MainMenu_Entry";
}
void AMainBaseGameMode::SaveGame()
{
	/*
	AMyPlayerState* PS = Cast<AMyPlayerState>(GameState->PlayerArray[0]);
	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SlotName, 0);
	if (PS)
	{
		PS->SavePlayState(CurrentSaveGame);
	}
	*/
	UMySaveGame* Instance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	if (Instance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Save--------Before Save Instance->TotalCoin = %f"),Instance->TotalCoin);
		MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		AMyPlayerState* MyPlayerState = MyCharacter->GetPlayerState<AMyPlayerState>();
		if (MyPlayerState)
		{
			FString CurrentLevelName = GetWorld()->GetMapName();
			CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
			if (CurrentLevelName != "Level_3")
			{
				Instance->TotalCoin = MyPlayerState->TotalCoin;
				Instance->SavedLevelName = NextLevelName;
				UE_LOG(LogTemp, Warning, TEXT("Save--------TorchTime Level Name :%s"), *GetWorld()->GetMapName());
				UE_LOG(LogTemp, Warning, TEXT("Save--------Save OK Instance->TotalCoin = %f"), Instance->TotalCoin);
				UE_LOG(LogTemp, Warning, TEXT("Save--------Save OK Instance->SavedLevelName = %s"), *Instance->SavedLevelName.ToString());
				UGameplayStatics::SaveGameToSlot(Instance, TEXT("MySaveGame"), 0);
			}
		}
	}
}

void AMainBaseGameMode::InitializeGame()
{
	UMySaveGame* Instance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	if (Instance)
	{
		Instance->TotalCoin = 0;
		Instance->SavedLevelName = "Level_1";
		
		UGameplayStatics::SaveGameToSlot(Instance, TEXT("MySaveGame"), 0);
	}
}

void AMainBaseGameMode::LoadGame()
{
	/*
	if (UGameplayStatics::DoesSaveGameExist(SlotName,0))
	{
		CurrentSaveGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

	}
	else {
		CurrentSaveGame = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(USaveGame::StaticClass()));
	}
	*/
	UMySaveGame* Instance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MySaveGame"), 0));
	if (Instance)
	{
		FString CurrentLevelName = GetWorld()->GetMapName();
		CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
		if (CurrentLevelName == "MainMenu_Entry") {
			NextLevelName = Instance->SavedLevelName;
		}
		MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (MyCharacter)
		{
			AMyPlayerState* MyPlayerState = MyCharacter->GetPlayerState<AMyPlayerState>();
			if (MyPlayerState)
			{
				MyPlayerState->TotalCoin = Instance->TotalCoin;
				UE_LOG(LogTemp, Warning, TEXT("Load-----Load TotalCoin OK,,,,%f"), MyPlayerState->TotalCoin);
			}
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Load filed becuse file is not excest"));
		Instance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
		Instance->TotalCoin = 0;
		Instance->SavedLevelName = "MainMenu_Entry";
		UGameplayStatics::SaveGameToSlot(Instance, TEXT("MySaveGame"), 0);
	}
}

void AMainBaseGameMode::StartPlay()
{
	Super::StartPlay();
	FString CurrentLevel = GetWorld()->GetMapName();
	CurrentLevel.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	UE_LOG(LogTemp, Error, TEXT("Start-----Currunt Level Name :%s"), *CurrentLevel);
	UE_LOG(LogTemp, Error, TEXT("Start-----Next Level Name :%s"),*NextLevelName.ToString());
	if (CurrentLevel == "Level_1")
	{
		InitializeGame();
		LoadGame();
	}
	else 
	{
		LoadGame();
	}
}

bool AMainBaseGameMode::IsGoToNextLevel(AMyCharacter* Character)
{
	UAttributeComponent* Attribute = Cast<UAttributeComponent>(Character->AttributeComp);
	if (Attribute->GetCurrentCoin() >= TargetScore)
	{
		return true;
	}
	else
	{
		return false;
	}
}
