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
	

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
};
