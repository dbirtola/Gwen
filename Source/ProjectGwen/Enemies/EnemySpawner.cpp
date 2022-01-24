// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "AbilitySystemComponent.h"
#include "EnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyTypeData.h"

TArray<UEnemyTypeData*> AEnemySpawner::GetValidEnemyTypes(int32 WaveLevel)
{
	TArray<UEnemyTypeData*> ValidTypes;

	for(UEnemyTypeData* EnemyType : EnemyTypes)
	{
		if(EnemyType->MinimumWaveForSpawning <= WaveLevel)
		{
			ValidTypes.Add(EnemyType);
		}
	}
	return ValidTypes;
}

UEnemyTypeData* AEnemySpawner::GetRandomValidEnemyType(int32 WaveLevel, int32 MaximumEnemyPower)
{
	TArray<UEnemyTypeData*> EnemyTypeCandidates = GetValidEnemyTypes(WaveLevel);
	EnemyTypeCandidates.RemoveAll([MaximumEnemyPower](const UEnemyTypeData* EnemyTypeData) { return EnemyTypeData->EnemyPowerLevel > MaximumEnemyPower;});

	if(EnemyTypeCandidates.IsEmpty())
	{
		// No valid enemies for these parameters
		return nullptr;
	}
	
	int32 Index = FMath::TruncToInt((FMath::RandRange(0, EnemyTypeCandidates.Num())));
	// I guess randrange is inclusive so theoretically we if we hit EnemyTypeCandidates.Num() we would crash. but thats insanely unlikely. either way:
	if(Index == EnemyTypeCandidates.Num())
	{
		Index--;
	}
	return EnemyTypeCandidates[Index];
}

TArray<AEnemySpawnPoint*> AEnemySpawner::GetValidSpawnPoints(int32 WaveLevel)
{
	TArray<AEnemySpawnPoint*> ValidSpawnPoints = SpawnPoints;
	//ValidSpawnPoints.RemoveAll([WaveLevel](AEnemySpawnPoint* SpawnPoint) { return SpawnPoint->MinimumWave > WaveLevel;});
	return ValidSpawnPoints;
}

AEnemySpawnPoint* AEnemySpawner::GetRandomValidSpawnPoint(int32 WaveLevel)
{
	TArray<AEnemySpawnPoint*> ValidSpawnPoints = GetValidSpawnPoints(WaveLevel);

	if(ValidSpawnPoints.IsEmpty())
	{
		return nullptr;
	}
	
	int32 Index = FMath::TruncToInt((FMath::RandRange(0, ValidSpawnPoints.Num())));
	// I guess randrange is inclusive so theoretically we if we hit ValidSpawnPoints.Num() we would crash. but thats insanely unlikely. either way:
	if(Index == ValidSpawnPoints.Num())
	{
		Index--;
	}
	return ValidSpawnPoints[Index];
}

void AEnemySpawner::BeginPlay()
{
	for(TObjectIterator<UEnemyTypeData> It; It; ++It)
	{
		EnemyTypes.Add(*It);
	}

	TArray<AActor*> SpawnPointActors;
	UGameplayStatics::GetAllActorsOfClass(this, AEnemySpawnPoint::StaticClass(), SpawnPointActors);
	for(AActor* SpawnPointActor : SpawnPointActors)
	{
		SpawnPoints.Add(Cast<AEnemySpawnPoint>(SpawnPointActor));
	}
}


void AEnemySpawner::GenerateWave(int32 WaveNumber)
{
	if(WavePowerCurve && WaveNumber >= 1)
	{
		float WavePower = WavePowerCurve->GetFloatValue(WaveNumber);

		// Generate our list of enemies we'll be fighting this wave
		float WavePowerRemaining = WavePower;
		while(WavePowerRemaining > 0)
		{
			UEnemyTypeData* Enemy = GetRandomValidEnemyType(WaveNumber, WavePowerRemaining);
			if(Enemy)
			{
				EnemiesToSpawn.Add(Enemy);
				WavePowerRemaining -= Enemy->EnemyPowerLevel;
			}
			else
			{
				return;
			}
		}
	}
}

void AEnemySpawner::StartWave(int32 WaveNumber)
{
	CurrentWave = WaveNumber;
	GenerateWave(WaveNumber);
	SpawnNextEnemyInWave();
}

bool AEnemySpawner::SpawnNextEnemyInWave()
{
	if(!EnemiesToSpawn.IsEmpty())
	{
		UEnemyTypeData* Enemy = EnemiesToSpawn.Pop();
		AEnemySpawnPoint* SpawnPoint = GetRandomValidSpawnPoint(CurrentWave);
		if(SpawnPoint && Enemy)
		{
			SpawnEnemy(Enemy, SpawnPoint->GetTransform());
			return true;
		}
	}

	// Happens if the wave is over or we couldnt get a valid spawn point for whatever reason
	return false;
}

bool AEnemySpawner::IsWaveFinished()
{
	return EnemiesToSpawn.IsEmpty();
}

void AEnemySpawner::SpawnEnemy(UEnemyTypeData* EnemyData, const FTransform& SpawnTransform)
{
	if(EnemyData)
	{
		AEnemyBase* Enemy = Cast<AEnemyBase>(GetWorld()->SpawnActor(EnemyData->BaseClass, &SpawnTransform));

		if(Enemy)
		{
			Enemy->EnemyTypeData = EnemyData;
			
			if(EnemyData->MeshOverride)
			{
				Enemy->GetMesh()->SetSkeletalMesh(EnemyData->MeshOverride);
			}

			if(EnemyData->AnimBPOverride)
			{
				Enemy->GetMesh()->SetAnimClass(EnemyData->AnimBPOverride);
			}

			if(UAbilitySystemComponent* ASC = Enemy->GetAbilitySystemComponent())
			{
				for(TSubclassOf<UGameplayEffect> Effect : EnemyData->SpawnEffects)
				{
					if(Effect)
					{
						FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
						ASC->ApplyGameplayEffectToSelf(Effect->GetDefaultObject<UGameplayEffect>(), 1, Context);	
					}
				}
			}
			
			// TODO: On hit effects
		}
	}
}
