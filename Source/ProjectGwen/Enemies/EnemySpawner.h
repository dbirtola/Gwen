// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EnemySpawner.generated.h"

/**
 * 
 */

class UEnemyTypeData;

UCLASS(Blueprintable)
class PROJECTGWEN_API AEnemySpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MinimumWave = 1;
};

UCLASS()
class PROJECTGWEN_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<UEnemyTypeData*> EnemyTypes;

	UPROPERTY()
	TArray<AEnemySpawnPoint*> SpawnPoints;

	TArray<UEnemyTypeData*> GetValidEnemyTypes(int32 WaveLevel);
	UEnemyTypeData* GetRandomValidEnemyType(int32 WaveLevel, int32 MaximumEnemyPower);
	TArray<AEnemySpawnPoint*> GetValidSpawnPoints(int32 WaveLevel);
	AEnemySpawnPoint* GetRandomValidSpawnPoint(int32 WaveLevel);

	// Enemies left to spawn in this wave. Populated on calls to StartWave
	UPROPERTY()
	TArray<UEnemyTypeData*> EnemiesToSpawn;
public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 CurrentWave = 0;
	
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCurveFloat* WavePowerCurve;

	void GenerateWave(int32 WaveNumber);
	
	UFUNCTION(BlueprintCallable)
	void SpawnEnemy(UEnemyTypeData* EnemyData, const FTransform& SpawnTransform);


	UFUNCTION(BlueprintCallable)
	void StartWave(int32 WaveNumber);
	
	UFUNCTION(BlueprintCallable)
	bool SpawnNextEnemyInWave();

	UFUNCTION(BlueprintPure)
	bool IsWaveFinished();
};
