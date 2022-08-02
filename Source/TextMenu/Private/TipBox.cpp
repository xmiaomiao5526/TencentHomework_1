// Fill out your copyright notice in the Description page of Project Settings.


#include "TipBox.h"
#include "Components/BoxComponent.h"
//#include "Blueprint/UserWidget.h"
#include "MyCharacterPlayerController.h"
#include "Engine/World.h"

// Sets default values
ATipBox::ATipBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tips = FText::FromString(" ");
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");

}

// Called when the game starts or when spawned
void ATipBox::BeginPlay()
{
	Super::BeginPlay();
	MyPlayerController = Cast<AMyCharacterPlayerController>(GetWorld()->GetFirstPlayerController());
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATipBox::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ATipBox::OnOverlapEnd);
}

// Called every frame
void ATipBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATipBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->IsChildOf(APawn::StaticClass()))
	{
		if (MyPlayerController)
		{
			MyPlayerController->ShowTips(Tips);
		}
	}
}

void ATipBox::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (MyPlayerController)
	{
		MyPlayerController->CloseTips();
	}
	Destroy();
}

