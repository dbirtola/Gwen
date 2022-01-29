// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "PaulsUtilities/Public/PooledActor.h"
#include "FireNodeComponent.generated.h"



USTRUCT()
struct PAULSUTILITIES_API FireNodeData {
	GENERATED_BODY()
	int32 Fuel;  //unsigned
	int16 BurnPerTick;  //unsigned
};

UCLASS()
class PAULSUTILITIES_API UFireNodeComponent : public UActorComponent {
	GENERATED_BODY()
public:
	FireNodeData NodeData;
	UFireNodeComponent() {}

	UFUNCTION(BlueprintImplementableEvent, Category = "PaulsUtilities | fire")
	void OnBurnTick();
	UFUNCTION(BlueprintImplementableEvent, Category = "PaulsUtilities | fire")
	void OnFinishedBurning();
};
