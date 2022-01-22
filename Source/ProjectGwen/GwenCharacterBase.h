// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UObject/Object.h"
#include "AbilitySystemInterface.h"
#include "PlayerAttributeSet.h"
#include "GwenCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGWEN_API AGwenCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AGwenCharacterBase();
	
	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPlayerAttributeSet* AttributeSet;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;

	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
