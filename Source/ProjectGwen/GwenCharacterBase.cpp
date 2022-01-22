// Fill out your copyright notice in the Description page of Project Settings.


#include "GwenCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"


AGwenCharacterBase::AGwenCharacterBase()
{

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
	AttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(FName("PlayerAttribute"));
	AbilitySystemComponent->AddAttributeSetSubobject(AttributeSet);
}

void AGwenCharacterBase::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

		
	if(AttributeSet)
	{
		GetCharacterMovement()->MaxWalkSpeed = AttributeSet->GetCurrentSpeed();
	}
}


UAbilitySystemComponent* AGwenCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
