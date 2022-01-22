// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

#include "AbilitySystemComponent.h"
#include "ProjectGwen/PlayerAttributeSet.h"

AEnemyBase::AEnemyBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(FName("Ability System Component"));
	EnemyAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(FName("Player Attribute Set"));
	AbilitySystemComponent->AddAttributeSetSubobject(EnemyAttributeSet);
}

UAbilitySystemComponent* AEnemyBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
