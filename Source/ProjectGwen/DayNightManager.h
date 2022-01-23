// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DayNightManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGenericDynamicMulticastDelegate);

USTRUCT(BlueprintType)
struct FTimeOfDay
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Hour;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Minutes;
};

/**
 * 
 */
UCLASS()
class PROJECTGWEN_API ADayNightManager : public AActor
{
	const float SkipToTimeMax = 99999;
	GENERATED_BODY()



	// legit forget the syntax for max float in ue4
	float SkipToTime = SkipToTimeMax;
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// time of day measured in 24 hour time, by seconds.
	float TimeOfDay = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTimeOfDay DaytimeStartTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTimeOfDay NighttimeStartTime;
	
	// Calculates speed based on how long we feel daytime should last
	UFUNCTION(BlueprintCallable)
	void SetDaytimeDuration(float RealSecondsOfDaytime);

	bool bPauseAtMidnight = true;

	bool bHasBroadcastedNightReached = false;
	bool bHasBroadcastedDayReached = false;
	
	// Measured in InGameMinutes per RealSecond. Overriden by calls to SetDaytimeDuration
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Speed = 20;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SkipSpeed = 120;
	
	UFUNCTION(BlueprintCallable)
	void FastForwardTime(int32 Hour, int32 Minutes);

	UFUNCTION(BlueprintCallable)
	void FastForwardToDaytime();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor* LightSource;
	
	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

	void AdjustLightActor();

	UPROPERTY(BlueprintAssignable)
	FGenericDynamicMulticastDelegate OnNightReached;

	UPROPERTY(BlueprintAssignable)
	FGenericDynamicMulticastDelegate OnDayReached;
};
