// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/SphereComponent.h"
#include "NovaramaProjectGameMode.h"
#include "NovaramaProjectGameInstance.h"
#include "NovaramaProjectCharacter.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Init the Sphere collision 
	mCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	mCollision->SetupAttachment(RootComponent);
	mCollision->SetCollisionResponseToChannels(ECollisionResponse::ECR_Overlap);
	mCollision->SetSphereRadius(50.f);

	//Init the Health component
	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	damage = 10.f;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	//Set custom collision to sphere collision
	mCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::MyBeginOverlap);
	mCollision->OnComponentEndOverlap.AddDynamic(this, &AEnemy::MyOverlapEnd);

	TArray<UActorComponent*> mSphere;
	mSphere = GetComponentsByTag(USphereComponent::StaticClass(), TEXT("AttackCollision"));
	//Set custom collision to sphere collision attack
	USphereComponent* mCollisionAttack = Cast<USphereComponent>(mSphere[0]);
	mCollisionAttack->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::AttackBeginOverlap);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (healthComponent->CurrentHealth < 0)
	{
		Destroy();
	}

}

void AEnemy::MyBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Control if the collision if with the player to start the animation  attack
	ANovaramaProjectCharacter* player = Cast<ANovaramaProjectCharacter>(OtherActor);
	if (player) {

		IsAttacking = true;
	}

}

void AEnemy::MyOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//Control when the collision end to stop de animation attack
	ANovaramaProjectCharacter* player = Cast<ANovaramaProjectCharacter>(OtherActor);
	if (player) {
		IsAttacking = false;
	}
}

void AEnemy::AttackBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Control if the sphere collision attack if hit the player and caused damage, if the player don't have health call to change the map
	ANovaramaProjectCharacter* player = Cast<ANovaramaProjectCharacter>(OtherActor);
	if (player)
	{
		if (player->healthComponent->CurrentHealth > 0) {
			player->healthComponent->LoseHealth(damage);
		}
		else {
			ANovaramaProjectGameMode* gamemode = Cast<ANovaramaProjectGameMode>(GetWorld()->GetAuthGameMode());
			UNovaramaProjectGameInstance*gameinstance = Cast<UNovaramaProjectGameInstance>(GetWorld()->GetGameInstance());
			if (gamemode&&gameinstance)
			{
				gameinstance->isDead = true;
				gamemode->ChangeMap(FName("MainMenu"));
				
			}
		}
	}
}