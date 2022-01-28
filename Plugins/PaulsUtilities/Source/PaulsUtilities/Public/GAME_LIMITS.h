#pragma once

/*
Target hardware:
* Some average 4 core cpu from 8 years ago
* 1.9GB max ram usage (this might be increased to 4+)
* GPU = unknown
* Disk = unknown
* NetworkBandwidth = unknown

Expectations:
Only one World object is in use at a time.

TODO:
* Come up with memory and ms budgets for different various systems
*/

#include "GameFramework/Actor.h"
#include "Components/ShapeComponent.h"

namespace GAME_LIMITS {
	static constexpr uint32_t MAX_STATIC_ACTOR_COUNT = 8000; //Actors without movable bodies and tick
	static constexpr uint32_t MAX_DYNAMIC_ACTOR_COUNT = 200; //Actors with movable bodies and/or tick
	static constexpr uint32_t MAX_ACTOR_COUNT = MAX_STATIC_ACTOR_COUNT+MAX_DYNAMIC_ACTOR_COUNT;
	static constexpr uint32_t MAX_ACTOR_TYPES = 128;
	static constexpr uint32_t MAX_DYNAMIC_LIGHT_COUNT = 32;  //May change
	static constexpr uint32_t MAX_STATIONARY_LIGHT_COUNT = 0;  //Till we have a HISM manager
	static constexpr uint32_t MAX_POLIES_IN_VIEW = 100000;  //Very likely to change
};

//This'll give everyone a rough idea how much memory these things use.
//This probably doesn't account for deep/indirect data.
static constexpr int AACTOR_SIZE = sizeof(AActor);
static constexpr int UOBJECT_SIZE = sizeof(UObject);
static constexpr int UDATA_ASSET_SIZE = sizeof(UDataAsset);
static constexpr int UACTOR_COMPONENT_SIZE = sizeof(UActorComponent);
static constexpr int USCENE_COMPONENT_SIZE = sizeof(USceneComponent);
static constexpr int UPRIMITIVE_COMPONENT_SIZE = sizeof(UPrimitiveComponent);
static constexpr int USHAPE_COMPONENT_SIZE = sizeof(UShapeComponent);