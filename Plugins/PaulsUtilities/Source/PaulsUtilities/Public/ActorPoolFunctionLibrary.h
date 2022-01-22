// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ActorPoolFunctionLibrary.generated.h"

class APooledActor;

UCLASS()
class PAULSUTILITIES_API UActorPoolFunctionLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "PaulsUtilities")
    static APooledActor* actorPoolGetActor(UClass* classType, UWorld* world, const FTransform& transform);
    UFUNCTION(BlueprintCallable, Category = "PaulsUtilities")
    static void actorPoolReturnActor(APooledActor* actor);

};
