// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FireNodeComponent.h"
#include "FireSystemFunctionLibrary.generated.h"

UCLASS()
class PAULSUTILITIES_API UFireSystemFunctionLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "PaulsUtilities | system")
	static void FireSystemInit ();
	UFUNCTION(BlueprintCallable, Category = "PaulsUtilities | system | create | construct")
	static void FireActorEnlist (AActor* owner);
	UFUNCTION(BlueprintCallable, Category = "PaulsUtilities | system | destroy | destruct")
	static void FireActorDelist (AActor* owner);
	UFUNCTION(BlueprintCallable, Category = "PaulsUtilities | system")
	static void FireSystemTick ();
};
