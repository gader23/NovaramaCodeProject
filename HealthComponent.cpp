// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	CurrentHealth = MaxHealth;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::LoseHealth(float damage)
{
	//Check if can reduce health
	if (CurrentHealth > 0) {
		//Reduce the current health
		CurrentHealth = CurrentHealth - damage;
	}
}

float UHealthComponent::NormalizeHealth()
{
	//Divide the current helth with the maximun healt to get a percentage of the health
	float health = CurrentHealth / MaxHealth;
	return health;
}