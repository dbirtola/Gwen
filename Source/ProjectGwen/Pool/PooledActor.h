// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../deps/IO/IO.h"
#include "PooledActor.generated.h"

UCLASS()
class PROJECTGWEN_API APooledActor : public AActor {
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	APooledActor() {
		printErrorToScreen("UPooledActor not ready for use yet!");
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
