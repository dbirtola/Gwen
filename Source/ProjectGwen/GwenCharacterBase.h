// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Death")
	bool bIsAlive = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Death")
	float RagdollTime = 2.5f;

	UFUNCTION(BlueprintCallable, Category="Death")
	void EnableRagdoll();
	
	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPlayerAttributeSet* AttributeSet;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;

	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	FDelegateHandle HealthChangedDelegateHandle;
	
	virtual void BeginPlay() override;

	void OnCurrentHealthChanged(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintImplementableEvent, Category = "Attributes", meta=(DisplayName="OnHealthChanged"))
	void BP_OnHealthChanged(float Health, float OldHealth);
};
