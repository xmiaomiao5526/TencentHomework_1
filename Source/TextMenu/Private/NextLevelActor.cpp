// Fill out your copyright notice in the Description page of Project Settings.


#include "NextLevelActor.h"
#include "Components/BoxComponent.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "MainBaseGameMode.h"
#include "MyCharacterPlayerController.h"

// Sets default values
ANextLevelActor::ANextLevelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Volume = CreateDefaultSubobject<UBoxComponent>("Volume");
	RootComponent = Volume;

	Mash = CreateDefaultSubobject<UStaticMeshComponent>("Mash");
	Mash->SetupAttachment(RootComponent);
	//NextLevel = "level_1";
}

void ANextLevelActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
		if (MyCharacter)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				FName NextLevel;
				if (GM) {
					NextLevel = GM->NextLevelName;
				}
				FString CurrentLevel = *World->GetMapName();
				CurrentLevel.RemoveFromStart(World->StreamingLevelsPrefix);
				if (FName(CurrentLevel)!=NextLevel)
				{
					if (GM->IsGoToNextLevel(MyCharacter))
					{
						GM->SaveGame();
						UGameplayStatics::OpenLevel(World, NextLevel);
					}
					else {
						if (MyPlayerController)
						{
							MyPlayerController->ShowTips(FText::FromString("You have not reached your goal yet!!!"));
						}
					}
				}
			}
		}
	}
}

void ANextLevelActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
		if (!GM->IsGoToNextLevel(MyCharacter))
		{
			if (MyPlayerController)
			{
				MyPlayerController->CloseTips();
			}
		}
	}
}

// Called when the game starts or when spawned
void ANextLevelActor::BeginPlay()
{
	Super::BeginPlay();
	MyPlayerController = Cast<AMyCharacterPlayerController>(GetWorld()->GetFirstPlayerController());
	GM = GetWorld()->GetAuthGameMode<AMainBaseGameMode>();
	Volume->OnComponentBeginOverlap.AddDynamic(this, &ANextLevelActor::OnOverlapBegin);
	Volume->OnComponentEndOverlap.AddDynamic(this, &ANextLevelActor::OnOverlapEnd);
	
}

// Called every frame
void ANextLevelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}