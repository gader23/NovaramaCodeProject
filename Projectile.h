// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class NOVARAMAPROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void ShootProjectile(float speed);
private:
	/*Custom overlap function to damage the enemy when collider with the projectile*/
	UFUNCTION()
		void MyBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	/*The box collider of the projectile*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CapsuleCollision")
		UBoxComponent* mCollisionBox;
	/*The movement component of the projectile*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileMovement")
		UProjectileMovementComponent* ProjectileMovement;

	/*The damage of the projectile in the enemies*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float damage;

};
