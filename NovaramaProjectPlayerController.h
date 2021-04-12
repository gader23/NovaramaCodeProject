// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NovaramaProjectPlayerController.generated.h"

UCLASS()
class ANovaramaProjectPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ANovaramaProjectPlayerController();

protected:
	

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	UFUNCTION()
		void Shoot();
	UFUNCTION()
		void StopShoot();
	UFUNCTION()
		void RotatePlayer();
	UFUNCTION()
		void SpawnProjectile();
	UFUNCTION()
		void MoveForward(float amount);
	UFUNCTION()
		void MoveRight(float amount);
private:		
	UPROPERTY()
		FTimerHandle  mRotateHandle;
	UPROPERTY()
		FTimerHandle mSpawnHandle;
	UPROPERTY()
		bool bShooting;
};


