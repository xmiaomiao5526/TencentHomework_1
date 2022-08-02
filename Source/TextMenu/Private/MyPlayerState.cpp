// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"
#include "MySaveGame.h"


AMyPlayerState::AMyPlayerState()
{
	TotalCoin = 0;
	NextLevelName = "Level_1";
}

void AMyPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);
	AMyPlayerState* MyPS = Cast<AMyPlayerState>(PlayerState);
	if (MyPS)
	{
		MyPS->TotalCoin = TotalCoin;
	}
}

void AMyPlayerState::SavePlayState_Implementation(UMySaveGame* SaveObject)
{
	if (SaveObject)
	{
		SaveObject->TotalCoin = TotalCoin;
	}
}

void AMyPlayerState::LoadPlayState_Implementation(UMySaveGame* SaveObject)
{
	if (SaveObject)
	{
		TotalCoin = SaveObject->TotalCoin;
	}
}
