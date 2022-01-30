// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DetourCrowdAIController.h" //Not sure about this one -> just in case.
#include "Navigation/CrowdFollowingComponent.h" 

#include "SupplementalAiLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGWEN_API USupplementalAiLibrary : public UBlueprintFunctionLibrary
{
		GENERATED_BODY()
public:

		//UFUNCTION(BlueprintCallable, Category = DetourCrowd)
		//static void SetSeparationWeight(UCrowdFollowingComponent* inCrowdFolowingComponent, int32 inWeight);
	
};
