// Fill out your copyright notice in the Description page of Project Settings.


#include "DayNightManager.h"

void ADayNightManager::SetDaytimeDuration(float RealSecondsOfDaytime)
{
	float DaytimeStartMinutes = (DaytimeStartTime.Hour * 60) + DaytimeStartTime.Minutes;
	float NighttimeStartMinutes = (NighttimeStartTime.Hour * 60) + NighttimeStartTime.Minutes;

	float TotalMinutes= NighttimeStartMinutes - DaytimeStartMinutes;
	float InGameMinutesPerRealSecond = TotalMinutes / RealSecondsOfDaytime;
	Speed = InGameMinutesPerRealSecond;
}

void ADayNightManager::FastForwardTime(int32 Hour, int32 Minutes)
{
	SkipToTime = (Hour * 60) + Minutes;
}

void ADayNightManager::FastForwardToDaytime()
{
	FastForwardTime(DaytimeStartTime.Hour, DaytimeStartTime.Minutes);
}


void ADayNightManager::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	float TimeSpeed = SkipToTime == SkipToTimeMax ? Speed : SkipSpeed;

	float OldTimeOfDay = TimeOfDay;
	TimeOfDay += TimeSpeed * DeltaTime;

	float NightFallMinutes = (NighttimeStartTime.Hour * 60) + NighttimeStartTime.Minutes;

	// broadcast night reached
	if(TimeOfDay > NightFallMinutes && !bHasBroadcastedNightReached)
	{
		bHasBroadcastedNightReached = true;
		OnNightReached.Broadcast();
	}
	
	float DaytimeStartMinutes = (DaytimeStartTime.Hour * 60) + DaytimeStartTime.Minutes;

	// broadcast day reached
	if(TimeOfDay > DaytimeStartMinutes && !bHasBroadcastedDayReached)
	{
		bHasBroadcastedDayReached = true;
		OnDayReached.Broadcast();
	}
	
	if(TimeOfDay >= (24*60))
	{
		// Just to make the editor view more clear that time is paused
		TimeOfDay = 24*60;
		
		// Don't pause during a fast-forward
		if(bPauseAtMidnight)
		{
			// Wait for a skip to get called to let us know we can proceed
			if(SkipToTime != SkipToTimeMax)
			{
				TimeOfDay = 0;
				bHasBroadcastedNightReached = false;
				bHasBroadcastedDayReached = false;
			}
			else
			{
				return;
			}
		}
	}
	
	if(OldTimeOfDay < SkipToTime && TimeOfDay > SkipToTime)
	{
		SkipToTime = SkipToTimeMax;
	}
	AdjustLightActor();
}

void ADayNightManager::AdjustLightActor()
{
	if(LightSource)
	{
		// y = 0 points to a right angle so uhhh, lets just consider that 6:00.
	
		float PercentThroughoutDay = TimeOfDay / (24*60);
		
		FRotator Rotator = FRotator::MakeFromEuler(FVector(0, (PercentThroughoutDay * 360.0f) + 90, 0));
		LightSource->SetActorRotation(Rotator, ETeleportType::ResetPhysics);
	}
}
