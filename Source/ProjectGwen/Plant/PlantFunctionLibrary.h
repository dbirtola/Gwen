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
	UFUNCTION(BlueprintCallable, Category = "Plant | system | create | construct")
	static APlantActor* PlantEnlist(TSubclassOf<APlantActor> ClassType, AActor* SpawningActor, const FTransform& Transform);
	UFUNCTION(BlueprintCallable, Category = "Plant | system | destroy | destruct")
	static void PlantDelist(APlantActor* PlantActor);
	UFUNCTION(BlueprintCallable, Category = "Plant")
	static void PlantSystemTick();
	UFUNCTION(BlueprintCallable, Category = "Plant")
	static void PlantSystemEnd();
};
