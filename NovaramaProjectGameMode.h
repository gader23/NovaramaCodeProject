// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Enemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "NovaramaProjectGameMode.generated.h"

UCLASS(minimalapi)
class ANovaramaProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANovaramaProjectGameMode();

	// Called when the game starts
	virtual void BeginPlay() override;

	/*Function that spawn the enemy in the level*/
	UFUNCTION(BlueprintCallable)
		void SpawnEnemy();

	/*Function to change the level*/
	UFUNCTION(BlueprintCallable)
		void ChangeMap(FName name);

	/*Reference of the enemy class*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* enemyClass;

	/*Reference of the BehaviorTree of the IA*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBehaviorTree* enemyBT;
	/*To control the main menu level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isDead;
};



