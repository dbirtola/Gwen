// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PlantActor.h"
#include "ActorPoolFunctionLibrary.h"
#include "PooledActor.h"
#include "PlantFunctionLibrary.generated.h"

//class APooledActor;

UCLASS()
class UPlantFunctionLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Plant")
	static APlantActor* PlantCreate(TSubclassOf<APlantActor> classType, UWorld* world, const FTransform& transform);
	UFUNCTION(BlueprintCallable, Category = "Plant")
	static void PlantSystemTick();
};
