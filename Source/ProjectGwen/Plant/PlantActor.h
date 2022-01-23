// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlantActor.generated.h"

UCLASS()
class APlantActor : public AActor {
	GENERATED_BODY()
	uint32_t currentGrowth = 0;
	uint32_t maxGrowth = 5000;
	uint32_t growthPerTick = 10;
public:
	APlantActor();
	
	// currently ticks growth by (uint32_t)(multiplier*10)
	FORCEINLINE void TickGrowth(float multiplier = 1) {
		uint32_t newGrowth = growthPerTick * multiplier + currentGrowth;
		if(maxGrowth < newGrowth) {
			currentGrowth = maxGrowth;
			SwapMeshOnCompletedGrowth();
		}
		currentGrowth = newGrowth;
	}

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "growth | max")
	//positive values only
	void SetMaxGrowth(int32 NewMaxGrowth) {
		maxGrowth = (uint32_t)NewMaxGrowth;
	}
	UFUNCTION(BlueprintCallable, Category = "growth | swap")
	virtual void SwapMeshOnMiddleGrowth() {}
	UFUNCTION(BlueprintCallable, Category = "growth | swap")
	virtual void SwapMeshOnCompletedGrowth() {}
};
