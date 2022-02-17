// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
//#include "PlantFunctionLibrary.h"
#include "Styling/SlateBrush.h"
#include "GameFramework/Actor.h"
#include "PooledActor.h"
#include "Components/Image.h"
#include "PlantActor.generated.h"

class UGameplayEffect;

class APlantActor;

UCLASS(BlueprintType)
class UPlantData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName SeedName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* SeedIcon;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<APlantActor> PlantActorBlueprint;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<UGameplayEffect>> HarvestEffects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UParticleSystem* OnDamageTakenEmitter;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> FreshlyPlantedBlueprint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> QuarterGrownBlueprint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> HalfGrownBlueprint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> ThreeQuarterGrownBlueprint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> FullyGrownBlueprint;
};

UCLASS()
class APlantActor : public APooledActor {
	GENERATED_BODY()
	enum {
		STAGE_0_PERCENT,
		STAGE_25_PERCENT,
		STAGE_50_PERCENT,
		STAGE_75_PERCENT,
		STAGE_100_PERCENT
	};
public:
	int32 currentGrowth = 0;  //positive values only
	int32 maxGrowth = 5000;  //positive values only
	int32 growthPerTick = 10; //positive values only
	uint8_t currentStage = STAGE_0_PERCENT;
	
	APlantActor();
	
	// currently ticks growth by (uint32_t)(multiplier*10)
	FORCEINLINE void TickGrowth(float multiplier = 1) {
		int32 newGrowth = growthPerTick * multiplier + currentGrowth;
		if(maxGrowth < newGrowth) 
			currentGrowth = maxGrowth;
		else
			currentGrowth = newGrowth;
		advancePlantStage();
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPlantData* PlantData;
	
	UFUNCTION(BlueprintCallable, Category = "growth | plant")
	void DelistSelf();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "growth | mesh | plant")
	void SwapMeshOn25PercentGrowth();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "growth | mesh | plant")
	void SwapMeshOn50PercentGrowth();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "growth | mesh | plant")
	void SwapMeshOn75PercentGrowth();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "growth | mesh | plant")
	void SwapMeshOnCompletedGrowth();
	UFUNCTION(BlueprintCallable, Category = "growth | plant")
	bool IsFullyGrown() {
		if (currentGrowth >= maxGrowth)
			return true;
		return false;
	}
	bool Is25PercentGrown() {
		if (currentGrowth >= maxGrowth/4)
			return true;
		return false;
	}
	bool Is50PercentGrown() {
		if (currentGrowth >= maxGrowth/2)
			return true;
		return false;
	}
	bool Is75PercentGrown(){
		if(currentGrowth >= maxGrowth*0.75)
			return true;
		return false;
	}

	void advancePlantStage() {
		switch(currentStage) {
		case STAGE_0_PERCENT:
			if(Is25PercentGrown()) {
				SwapMeshOn25PercentGrowth();
				currentStage++;
			}
			return;
		case STAGE_25_PERCENT:
			if(Is50PercentGrown()) {
				SwapMeshOn50PercentGrowth();
				currentStage++;
			}
			return;
		case STAGE_50_PERCENT:
			if(Is75PercentGrown()) {
				SwapMeshOn75PercentGrowth();
				currentStage++;
			}
			return;
		case STAGE_75_PERCENT:
			if(IsFullyGrown())
			{
				SwapMeshOnCompletedGrowth();
				currentStage++;
			}
			return;
		case STAGE_100_PERCENT:
			return;
		}
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UGameplayEffect> GameplayEffects;
};
