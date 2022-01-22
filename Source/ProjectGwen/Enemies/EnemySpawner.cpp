// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "EnemyBase.h"

void AEnemySpawner::SpawnEnemy(UEnemyTypeData* EnemyData, const FTransform& SpawnTransform)
{
	if(EnemyData)
	{
		AEnemyBase* Enemy = Cast<AEnemyBase>(GetWorld()->SpawnActor(EnemyData->BaseClass, &SpawnTransform));

		if(EnemyData->MeshOverride)
		{
			Enemy->GetMesh()->SetSkeletalMesh(EnemyData->MeshOverride);
		}

		if(EnemyData->AnimBPOverride)
		{
			Enemy->GetMesh()->SetAnimClass(EnemyData->AnimBPOverride);
		}
	}
}
