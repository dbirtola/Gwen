// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyTypeData.h"
#include "UObject/Object.h"
#include "EnemySpawner.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGWEN_API AEnemySpawner : public AActor
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable)
	void SpawnEnemy(UEnemyTypeData* EnemyData, const FTransform& SpawnTransform);
};
