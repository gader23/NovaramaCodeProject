// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "NovaramaProjectGameMode.h"
#include "NovaramaProjectPlayerController.h"
#include "NovaramaProjectCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"

ANovaramaProjectGameMode::ANovaramaProjectGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ANovaramaProjectPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	isDead = false;
}

// Called when the game starts
void ANovaramaProjectGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	// ...

}

void ANovaramaProjectGameMode::SpawnEnemy()
{
	//Get the spawn point of the enemy
	TArray<AActor*> SpawnPoints;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Spawn"), SpawnPoints);
	//Spawn the enemy
	if (SpawnPoints.Num()>0) {
		int rand=FMath::RandRange(0, 3);
		APawn* enemy = UAIBlueprintHelperLibrary::SpawnAIFromClass(GetWorld(), enemyClass, enemyBT, SpawnPoints[rand]->GetActorLocation(), SpawnPoints[rand]->GetActorRotation());
	}
}

void ANovaramaProjectGameMode::ChangeMap(FName name)
{
	//Get the game instance to can change the level
	UGameInstance *gameInstance = Cast<UGameInstance>(GetGameInstance());
	//Change the level of the game
	UGameplayStatics::OpenLevel((UObject*)gameInstance, name);
}
