// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttributeSet.h"

void UPlayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if(GetCurrentHealth() <= 0)
	{
		GetOwningActor()->Destroy();
	}
}
