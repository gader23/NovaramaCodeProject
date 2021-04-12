// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Projectile.h"
#include "HealthComponent.h"
#include "NovaramaProjectCharacter.generated.h"

UCLASS(Blueprintable)
class ANovaramaProjectCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANovaramaProjectCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }
	/*Function to shoot the projectile of the gun*/
	UFUNCTION()
		void Fire();
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
	/*A reference to projectile that spawn when shoot*/
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<AProjectile>ProjectileBluePrint;
	/*The Speed of the projectile*/
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		float ProjectileSpeed = 1000;
public:
	/*Health componet to control the health of the character*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UHealthComponent* healthComponent;
};

