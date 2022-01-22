// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
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

		if(UAbilitySystemComponent* ASC = Enemy->GetAbilitySystemComponent())
		{
			for(UGameplayEffect* Effect : EnemyData->EnemyEffects)
			{
				FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
				ASC->ApplyGameplayEffectToSelf(Effect, 1, Context);
			}
		}
	}
}
