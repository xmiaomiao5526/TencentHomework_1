// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "AttributeComponent.h"
#include "MyPlayerState.h"
#include "MyCharacter.h"

ACoin::ACoin() {
	CoinValue = 1;
	SetIsRotateDefault(true);
	SetRotateSpeedDefault(180);
}

void ACoin::PickUp(AActor* OtherActor)
{
	if (OtherActor)
	{
		UAttributeComponent* AttributeComp = Cast<UAttributeComponent>(OtherActor->GetComponentByClass(UAttributeComponent::StaticClass()));
		
		if (AttributeComp)
		{
			AttributeComp->ApplyScoreChange(CoinValue);
		}
		AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
		if (MyCharacter)
		{
			AMyPlayerState* MyPlayerState = MyCharacter->GetPlayerState<AMyPlayerState>();
			if (MyPlayerState)
			{
				MyPlayerState->SetTotalCoin(CoinValue);
			}
		}
	}
}

void ACoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
};
