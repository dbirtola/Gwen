// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ShapeComponent.h"
#include "UObject/Object.h"
#include "PooledActor.generated.h"

UCLASS()
class PROJECTGWEN_API UPooledActor : public UObject {
	GENERATED_BODY()
public:
	UPooledActor() {
		throw;  //TODO: replace with print message.
	}
};
