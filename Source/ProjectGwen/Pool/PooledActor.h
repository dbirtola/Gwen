// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../deps/IO/IO.h"
#include "../deps/FlatBuffer/FlatBuffer.h"
#include "../GAME_LIMITS.h"
#include "PooledActor.generated.h"

UCLASS()
class PROJECTGWEN_API APooledActor : public AActor {
	GENERATED_BODY()
	static TMap<FName, FlatBuffer<APooledActor*, GAME_LIMITS::MAX_ACTOR_COUNT>> pooledActors;
public:
	APooledActor() {
		printErrorToScreen("UPooledActor not ready for use yet!");
		if (pooledActors.Find(this->GetFName())) {
			pooledActors[this->GetFName()] = {};
			for (unsigned int i = 0; i < GAME_LIMITS::MAX_ACTOR_COUNT; i++) {
				pooledActors[this->GetFName()][i] = GetBasicClone();;
			}
		}
	}
	
private:
	APooledActor* GetBasicClone() {
		UWorld* World = this->GetWorld();
		FActorSpawnParameters params;
		params.Template = this;
		UClass* itemClass = this->GetClass();
		return World->SpawnActor<APooledActor>(itemClass, params);
	}
protected:
	virtual void BeginPlay() override {
		Super::BeginPlay();  //TODO: Is this needed?  Can this be set to = nullptr?
	}
public:
	virtual void Tick(float DeltaTime) override {
		Super::Tick(DeltaTime);  //TODO: Is this needed?
	}
};
