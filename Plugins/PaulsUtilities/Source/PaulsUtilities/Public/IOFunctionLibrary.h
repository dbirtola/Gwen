// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IOFunctionLibrary.generated.h"



UENUM(BlueprintType)
enum class EMyEnum : uint8
{
	Casted,
	Failed
};

UCLASS()
class PAULSUTILITIES_API UIOFunctionLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "PaulsUtilities | IO")
	static void printErrorToScreen(const FString& str) {
		FString errorMsg = "Error: ";
		errorMsg += str;
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 12.f, FColor::Red, errorMsg);
	}
	/*UFUNCTION(BlueprintCallable, Category = "PaulsUtilities | IO", Meta = (ExpandEnumAsExecs = "Branches"))
	template <class T>
	static UObject* castOrPrintError<T>(const AActor& obj, TEnumAsByte<EMyEnum>& Branches) {
		UObject* retValue = Cast<classType>(&obj);
	}*/
};
