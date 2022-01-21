// Fill out your copyright notice in the Description page of Project Settings.


#include "PooledActor.h"

TMap<FName, FlatBuffer<APooledActor*, GAME_LIMITS::MAX_ACTOR_COUNT>> APooledActor::pooledActors = {};
