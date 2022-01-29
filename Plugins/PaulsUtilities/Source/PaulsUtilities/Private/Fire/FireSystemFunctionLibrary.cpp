#include "Fire/FireSystemFunctionLibrary.h"
#include "FlatBuffer.h"
#include "Fire/FireSettingsComponent.h"
#include "PaulsUtilities/Public/GAME_LIMITS.H"

FlatBuffer<AActor*, GAME_LIMITS::MAX_ACTOR_COUNT> actorsWithFire;
FlatBuffer<FireSettingsData, GAME_LIMITS::MAX_ACTOR_COUNT> actorsFireSettings;

void UFireSystemFunctionLibrary::FireActorEnlist (AActor* owner) {
	
}
void UFireSystemFunctionLibrary::FireActorDelist (AActor* owner) {
	
}

void UFireSystemFunctionLibrary::FireSystemTick () {
	uint32_t count = actorsWithFire.count;
	for(uint32_t i = 0; i < count; i++) {
		AActor* actorWithFire = actorsWithFire[i];
		UFireSettingsComponent* fireSettings =
			(UFireSettingsComponent*)actorWithFire->GetComponentByClass(TSubclassOf<UFireSettingsComponent>());
		if(fireSettings == nullptr) continue;
	}
}