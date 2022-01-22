// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "UObject/Object.h"
#include "EnemyBase.generated.h"

class UAbilitySytemComponent;
class UPlayerAttributeSet;

/**
 * 
 */
UCLASS()
class PROJECTGWEN_API AEnemyBase : public ACharacter, public IAbilitySystemInterface
{
private:
	GENERATED_BODY()

	AEnemyBase();

	UPlayerAttributeSet* EnemyAttributeSet;
public:
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UAbilitySystemComponent* AbilitySystemComponent;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
