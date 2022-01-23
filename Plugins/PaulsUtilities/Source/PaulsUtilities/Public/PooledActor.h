// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledActor.generated.h"

UCLASS()
class PAULSUTILITIES_API APooledActor : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APooledActor();

	UFUNCTION(BlueprintCallable, Category = "PaulsUtilities")
	virtual void initOnGet();
	UFUNCTION(BlueprintCallable, Category = "PaulsUtilities")
	virtual void resetOnReturn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool canTickOnWakeup = false;
};
