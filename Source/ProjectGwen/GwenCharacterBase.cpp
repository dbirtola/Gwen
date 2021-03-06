// Fill out your copyright notice in the Description page of Project Settings.


#include "GwenCharacterBase.h"

#include "GameplayTagsManager.h"
#include "MeshAttributeArray.h"
#include "GameFramework/CharacterMovementComponent.h"


AGwenCharacterBase::AGwenCharacterBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
	AttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(FName("PlayerAttribute"));
	AbilitySystemComponent->AddAttributeSetSubobject(AttributeSet);
}

void AGwenCharacterBase::EnableRagdoll()
{
	GetMesh()->SetSimulatePhysics(true);
	GetCharacterMovement()->DisableMovement();
}

void AGwenCharacterBase::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

		
	if(AttributeSet)
	{
		GetCharacterMovement()->MaxWalkSpeed = AttributeSet->GetCurrentSpeed();
	}
	if(UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
	{
		if(ASC->HasMatchingGameplayTag(UGameplayTagsManager::Get().RequestGameplayTag(FName("Status.CrowdControl.Stun"))))
		{
			//GetCharacterMovement()->MovementMode = EMovementMode::MOVE_None;
		}
		else
		{
			//GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		}
	}
}


UAbilitySystemComponent* AGwenCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGwenCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		HealthChangedDelegateHandle = AbilitySystemComponent
		->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetCurrentHealthAttribute())
		.AddUObject(this, &AGwenCharacterBase::OnCurrentHealthChanged);
	}
}

void AGwenCharacterBase::OnCurrentHealthChanged(const FOnAttributeChangeData& Data)
{
	BP_OnHealthChanged(Data.NewValue, Data.OldValue);
}
