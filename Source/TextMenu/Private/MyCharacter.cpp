// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AttributeComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SuperPowerComponent.h"
#include "MainBaseGameMode.h"
#include "GameFramework/Actor.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 260;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;
	CameraComp->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));

	AttributeComp = CreateDefaultSubobject<UAttributeComponent>("AttributeComp");

	SuperPowerComp = CreateDefaultSubobject<USuperPowerComponent>("SuperPowerComp");

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("ShadowMesh");


	BaseTurnRate = 65;
	BaseLookupRate = 65;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,540,0);
	GetCharacterMovement()->JumpZVelocity = 450;
	GetCharacterMovement()->AirControl = 0.2f;

}
// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("My Character DeltaTime:%f,DeltaTime=0??:%d"), GetWorld()->GetDeltaSeconds(), GetWorld()->GetDeltaSeconds()==0)
	//SuperPowerComp->InitializeList(GetActorLocation());
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//SuperPowerComp->RefreshList(this, GetActorLocation());
	//UE_LOG(LogTemp, Error, TEXT("Point:%d"), SuperPowerComp)
	UE_LOG(LogTemp, Error, TEXT("Point:%d"), MeshComp)
		if (MeshComp)
		{
			SuperPowerComp->ShowFourSecondsAgoLoction<UStaticMeshComponent>(MeshComp);
		}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	//PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AMyCharacter::PrimaryInteract);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Lookup", this, &AMyCharacter::TurnLookupRate);

	PlayerInputComponent->BindAction("BackInTime", IE_Pressed, this,&AMyCharacter::BackInTime);

	PlayerInputComponent->BindAction("ReloadLevel", IE_Pressed, this, &AMyCharacter::ReloadGame);
}


void AMyCharacter::MoveForward(float Value)
{
	if (Controller && Value != 0) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
	
}

void AMyCharacter::MoveRight(float Value)
{
	if (Controller && Value != 0) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AMyCharacter::TurnAtRate(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->DeltaTimeSeconds);
}

void AMyCharacter::TurnLookupRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookupRate * GetWorld()->DeltaTimeSeconds);
}

/*
void AMyCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}*/

void AMyCharacter::BackInTime()
{
	UE_LOG(LogTemp, Error, TEXT("PUsh ------Point:%d"), SuperPowerComp)
	//UE_LOG(LogTemp, Error, TEXT("Point:%d,My Location =(%.2f,,%.2f,,%.2f)"), SuperPowerComp,SuperPowerComp->FourSecondsBeforeLoction.X, SuperPowerComp->FourSecondsBeforeLoction.Y, SuperPowerComp->FourSecondsBeforeLoction.Z)
	if (SuperPowerComp)
	{
		SuperPowerComp->TurnBackFourSecondsLoction();
	}
}

void AMyCharacter::ReloadGame()
{
	AMainBaseGameMode* GM = Cast<AMainBaseGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->LoadGame();
		UGameplayStatics::OpenLevel(GetWorld(),FName(*GetWorld()->GetMapName().Right(7)));
	}	
}


