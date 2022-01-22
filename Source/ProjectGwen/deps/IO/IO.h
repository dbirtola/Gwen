#pragma once

#include "Engine.h"

inline void printErrorToScreen(const FString& str) {
	FString errorMsg = "Error: ";
	errorMsg += str;
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 12.f, FColor::Red, errorMsg);
}