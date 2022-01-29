// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PlayerAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeDelegate, float, Health);

UCLASS()
class PROJECTGWEN_API UPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	FOnHealthChangeDelegate OnHealthChange;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData CurrentHealth = 100;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, CurrentHealth)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData MaximumHealth = 100;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MaximumHealth)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData CurrentSpeed = 600;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, CurrentSpeed)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData NumProjectiles = 1;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, NumProjectiles)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData ProjectileArc = 0;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, ProjectileArc)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData ProjectileExplosionRadius = 0;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, ProjectileExplosionRadius)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData ProjectileSpeed = 1200;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, ProjectileSpeed)

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
};
