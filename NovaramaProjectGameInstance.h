// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NovaramaProjectGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NOVARAMAPROJECT_API UNovaramaProjectGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isDead = false;
};
