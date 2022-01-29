// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantFunctionLibrary.h"
#include "../deps/FlatBuffer/FlatBuffer.h"
#include "PaulsUtilities/Public/GAME_LIMITS.h"
#include "PaulsUtilities/Public/IOFunctionLibrary.h"

FlatBuffer<APlantActor*, GAME_LIMITS::MAX_STATIC_ACTOR_COUNT> plantsToTick;

APlantActor* UPlantFunctionLibrary::PlantEnlist(TSubclassOf<APlantActor> ClassType, AActor* SpawningActor, const FTransform& Transform) {
	UWorld* world = SpawningActor->GetWorld();
	if(ClassType == nullptr) {
		UIOFunctionLibrary::printErrorToScreen("PlantFunctionLibrary::PlantCreate()'s ClassType was nullptr");
		return nullptr;  //TODO: Decide if we should just throw here instead.
	}
	APlantActor* plant = Cast<APlantActor>(UActorPoolFunctionLibrary::actorPoolGetActor(ClassType, world, Transform));
	if (plant == nullptr) {
		UIOFunctionLibrary::printErrorToScreen("PlantFunctionLibrary::PlantCreate() could not get another pooled APlantActor");
		return nullptr;  //TODO: Decide if we should just throw here instead.
	}
	if (plantsToTick.count == GAME_LIMITS::MAX_STATIC_ACTOR_COUNT) {
		UIOFunctionLibrary::printErrorToScreen("PlantFunctionLibrary::PlantCreate() has already reached it's max APlantActor count");
		return nullptr;  //TODO: Decide if we should just throw here instead.
	}
	plantsToTick.push(plant);
	return plant;
}
void UPlantFunctionLibrary::PlantDelist(APlantActor* PlantActor){
	uint32_t count = plantsToTick.count;
	for(uint32_t i = 0; i < count; i++) {
		APlantActor* compareTo = plantsToTick[i];
		if(PlantActor == compareTo) {
			plantsToTick.pop();
			plantsToTick[i] = plantsToTick[count];
			UActorPoolFunctionLibrary::actorPoolReturnActor(PlantActor);
			return;
		}
	}
	UIOFunctionLibrary::printErrorToScreen("PlantFunctionLibrary::PlantDelist()'s PlantActor doesn't exist in plantsToTick");
}

void UPlantFunctionLibrary::PlantSystemTick() {
	const uint32_t count = plantsToTick.count;
	for (uint32_t i = 0; i < count; i++) {
		if(IsValid(plantsToTick[i]))
		{
			plantsToTick[i]->TickGrowth();
		}
	}
}
void UPlantFunctionLibrary::PlantSystemEnd() {
	plantsToTick.count = 0;
}