// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "NovaramaProjectPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "NovaramaProjectCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "TimerManager.h"
#include "Engine/World.h"

ANovaramaProjectPlayerController::ANovaramaProjectPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	
}

void ANovaramaProjectPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	
}

void ANovaramaProjectPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("Shoot", IE_Pressed, this, &ANovaramaProjectPlayerController::Shoot);
	InputComponent->BindAction("Shoot", IE_Released, this,&ANovaramaProjectPlayerController::StopShoot);
	InputComponent->BindAxis("MoveForward",this, &ANovaramaProjectPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ANovaramaProjectPlayerController::MoveRight);
}

void ANovaramaProjectPlayerController::MoveForward(float amount)
{

	if (amount)
	{
		ANovaramaProjectCharacter*mPlayer = Cast<ANovaramaProjectCharacter>(GetPawn());
		FRotator rotator(0, mPlayer->GetControlRotation().Yaw, 0);
		mPlayer->AddMovementInput(UKismetMathLibrary::GetForwardVector(rotator), amount);

	}
}

void ANovaramaProjectPlayerController::MoveRight(float amount)
{
	if (amount)
	{
		ANovaramaProjectCharacter* mPlayer = Cast<ANovaramaProjectCharacter>(GetPawn());
		FRotator rotator(0, mPlayer->GetControlRotation().Yaw, 0);
		mPlayer->AddMovementInput(UKismetMathLibrary::GetRightVector(rotator), amount);

	}
}

void ANovaramaProjectPlayerController::Shoot()
{

		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("RotatePlayer"));
		GetWorld()->GetTimerManager().SetTimer(mRotateHandle, TimerDelegate, 0.01f, true);
		FTimerDelegate TimerDelegate2;
		TimerDelegate2.BindUFunction(this, FName("SpawnProjectile"));
		GetWorld()->GetTimerManager().SetTimer(mSpawnHandle, TimerDelegate2, 0.5f, true);
	
}

void ANovaramaProjectPlayerController::StopShoot()
{
	GetWorld()->GetTimerManager().ClearTimer(mRotateHandle);
	GetWorld()->GetTimerManager().ClearTimer(mSpawnHandle);
	bShooting = false;
}

void ANovaramaProjectPlayerController::RotatePlayer()
{
	ANovaramaProjectCharacter* mPlayer = Cast<ANovaramaProjectCharacter>(GetPawn());
	FVector mouselocation(mPlayer->GetCursorToWorld()->GetComponentLocation().X, mPlayer->GetCursorToWorld()->GetComponentLocation().Y, 0);
	FVector playerlocation(mPlayer->GetActorLocation().X, mPlayer->GetActorLocation().Y, 0);
	mPlayer->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(playerlocation, mouselocation));
	if (!bShooting)
	{
		ANovaramaProjectCharacter* mPlayer = Cast<ANovaramaProjectCharacter>(GetPawn());
		mPlayer->Fire();
		bShooting = true;
	}
	
}

void ANovaramaProjectPlayerController::SpawnProjectile()
{
	ANovaramaProjectCharacter* mPlayer = Cast<ANovaramaProjectCharacter>(GetPawn());
	mPlayer->Fire();
}


