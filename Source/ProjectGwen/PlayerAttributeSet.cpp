// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttributeSet.h"
#include "GameplayEffectExtension.h"

void UPlayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.f, GetMaximumHealth()));
		OnHealthChange.Broadcast(CurrentHealth.GetCurrentValue());
	}
}
