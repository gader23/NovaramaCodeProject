// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HealthComponent.h"
#include "Enemy.generated.h"

UCLASS()
class NOVARAMAPROJECT_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();
	/*Custom Collision for the Enemy to control the animations*/
	UFUNCTION()
		void MyBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void MyOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	/*Custom Collision for cause damage to the player*/
	UFUNCTION()
		void AttackBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/*Bool to control the animation of attack*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsAttacking;
	/*Sphere Collision of the enemy*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USphereComponent* mCollision;
	/*Health component of the enemy*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UHealthComponent* healthComponent;
	/*Damage that the enemy caused*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float damage;

};
