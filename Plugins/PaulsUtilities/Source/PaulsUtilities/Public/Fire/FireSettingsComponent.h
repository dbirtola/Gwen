// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "PaulsUtilities/Public/PooledActor.h"
#include "FireSettingsComponent.generated.h"



USTRUCT()
struct PAULSUTILITIES_API FireSettingsData {
	GENERATED_BODY()
	uint32 fireSystemID = -1;  //Private: no touchy!
	bool DestroyOwnerOnCompletion;
	FORCEINLINE bool isRegistered() const {
		if(fireSystemID != -1)
			return true;
		return false;
	}
};

UCLASS()
class PAULSUTILITIES_API UFireSettingsComponent : public UActorComponent {
	GENERATED_BODY()
public:
	FireSettingsData SettingsData;
	UFireSettingsComponent() {}
};
