﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EnemyTypeData.generated.h"

class UPlantData;
class AEnemyBase;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class PROJECTGWEN_API UEnemyTypeData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AEnemyBase> BaseClass;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USkeletalMesh* MeshOverride;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UAnimInstance> AnimBPOverride;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPlantData* SeedDropped;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<UGameplayEffect>> SpawnEffects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<UGameplayEffect>> OnHitEffects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 EnemyPowerLevel = 1;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MinimumWaveForSpawning = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UParticleSystem* OnHitEffect;
};
