// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Enemy.h"
#include "Engine/Engine.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Init the projectile movement component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bAutoActivate = false;
	ProjectileMovement->ProjectileGravityScale = 0;

	//Init the Box collision component
	mCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionCapsule"));
	mCollisionBox->SetupAttachment(RootComponent);
	mCollisionBox->SetCollisionResponseToChannels(ECollisionResponse::ECR_Overlap);

	damage = 30.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	//Set the custom collision to box collision
	mCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::MyBeginOverlap);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::ShootProjectile(float speed)
{
	//Add te velocity of the projectile
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	//Activate the component
	ProjectileMovement->Activate();
}

void AProjectile::MyBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Cast the actor that collision to projectile 
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	//If the actor is a Enemy the projectile cause damage to enemy and if the Enemy don't have health destroy the Enemy
	if (Enemy)
	{
		if (Enemy->healthComponent->CurrentHealth > 0) {
			Enemy->healthComponent->LoseHealth(damage);
		}
		else {
			Enemy->Destroy();
		}
	}

}