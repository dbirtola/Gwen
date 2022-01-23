﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantFunctionLibrary.h"
#include "../deps/FlatBuffer/FlatBuffer.h"
#include "../GAME_LIMITS.h"
#include "../deps/IO/IO.h"

FlatBuffer<APlantActor*, GAME_LIMITS::MAX_STATIC_ACTOR_COUNT> plantPool;

APlantActor* UPlantFunctionLibrary::PlantCreate(TSubclassOf<APlantActor> ClassType, AActor* SpawningActor, const FTransform& Transform) {
	UWorld* world = SpawningActor->GetWorld();
	if(ClassType == nullptr) {
		printErrorToScreen("PlantFunctionLibrary::PlantCreate()'s ClassType was nullptr");
		return nullptr;  //TODO: Decide if we should just throw here instead.
	}
	APlantActor* plant = Cast<APlantActor>(UActorPoolFunctionLibrary::actorPoolGetActor(ClassType, world, Transform));
	if (plant == nullptr) {
		printErrorToScreen("PlantFunctionLibrary::PlantCreate() could not get another pooled APlantActor");
		return nullptr;  //TODO: Decide if we should just throw here instead.
	}
	if (plantPool.count == GAME_LIMITS::MAX_STATIC_ACTOR_COUNT) {
		printErrorToScreen("PlantFunctionLibrary::PlantCreate() has already reached it's max APlantActor count");
		return nullptr;  //TODO: Decide if we should just throw here instead.
	}
	plantPool.push(plant);
	return plant;
}
void UPlantFunctionLibrary::PlantSystemTick() {
	const uint32_t count = plantPool.count;
	for (uint32_t i = 0; i < count; i++) {
		plantPool[i]->TickGrowth();
	}
}