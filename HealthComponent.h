// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NOVARAMAPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*Function to take off health*/
	UFUNCTION(BlueprintCallable)
		void LoseHealth(float damage);

	/*Function to get a normalize current health for can show the health bar*/
	UFUNCTION(BlueprintCallable)
		float NormalizeHealth();

	/*The Maximun health*/
	UPROPERTY(BlueprintReadOnly)
		float MaxHealth = 100.f;

	/*The current health*/
	UPROPERTY(BlueprintReadOnly)
		float CurrentHealth;
		
};
