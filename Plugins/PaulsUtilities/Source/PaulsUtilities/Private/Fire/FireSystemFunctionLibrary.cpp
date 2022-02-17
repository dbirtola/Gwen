#include "Fire/FireSystemFunctionLibrary.h"
#include "FlatBuffer.h"
#include "Fire/FireSettingsComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PaulsUtilities/Public/GAME_LIMITS.H"
#include "PaulsUtilities/Public/IOFunctionLibrary.h"

FlatBuffer<AActor*, GAME_LIMITS::MAX_ACTOR_COUNT> actorsWithFire;
FlatBuffer<FireSettingsData, GAME_LIMITS::MAX_ACTOR_COUNT> actorsFireSettings;

bool getFireStuff(AActor* owner, TArray<UFireNodeComponent*>* outFireNodes,
	UFireSettingsComponent* outFireSettings)
{
	UFireSettingsComponent* fireSettings =
		Cast<UFireSettingsComponent>(owner->GetComponentByClass(TSubclassOf<UFireSettingsComponent>()));
	if(fireSettings == nullptr) return false;
	TArray<UFireNodeComponent*> fireNodes;
	owner->GetComponents<UFireNodeComponent>(fireNodes);
	if(fireNodes.Num() == 0) {
		UIOFunctionLibrary::printErrorToScreen("getFireStuff()'s AActor* owner has a fire system but no nodes!");
		return false;
	}
	outFireSettings = fireSettings;
	*outFireNodes = fireNodes;
	return true;
}

void getOverlappingActorsInRadius(AActor* owner, float radius, TArray<AActor*>& outActors) {
	UWorld* world = owner->GetWorld();
	FVector pos = owner->GetTransform().GetLocation();
	//float radius = 50;
	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	//objectTypes.Add();
	TArray<AActor*> ignoredActors;  ignoredActors.Add(owner);
	EDrawDebugTrace::Type drawDebugType = EDrawDebugTrace::Type::ForDuration;
	TArray<FHitResult> hits;
	bool ignoreSelf = true;
	FLinearColor traceColor = {1, 1, 0, 1};
	FLinearColor traceHitColor = {1, 0.7f, 0, 1};
	float drawTime = 0.25;
			
	UKismetSystemLibrary::SphereTraceMultiForObjects(world, pos, pos, radius, objectTypes,
		false, ignoredActors, drawDebugType, hits, ignoreSelf, traceColor,
		traceHitColor, drawTime);
	TArray<AActor*> hitActors;
	uint32_t count = hits.Num();
	for (uint32_t i = 0; i < count; i++) {
		AActor* actor = hits[i].GetActor();
		for (uint32_t j = 0; j < (uint32_t)hitActors.Num(); j++)
			if(hitActors[j] == actor)
				goto onRedundent;
		hitActors.Add(actor);
		onRedundent:
		continue;
	}
}

void UFireSystemFunctionLibrary::FireSystemInit () {
	int32 coreCount = FPlatformMisc::NumberOfCoresIncludingHyperthreads();
	if (GThreadPool->GetNumThreads() != coreCount)
		GThreadPool->Create(coreCount);
}

void UFireSystemFunctionLibrary::FireActorEnlist (AActor* owner) {
	static TArray<UFireNodeComponent*> fireNodes = TArray<UFireNodeComponent*>();
	static UFireSettingsComponent* fireSettings = nullptr;
	bool hasAllFireStuff = getFireStuff(owner, &fireNodes, fireSettings);
	if(hasAllFireStuff == false) {
		UIOFunctionLibrary::printErrorToScreen("FireActorEnlist()'s owner doesn't have all fire components");
		return;
	}
	const uint32_t id = actorsWithFire.count;
	actorsWithFire.push(owner);
	fireSettings->SettingsData.fireSystemID = id;
	actorsFireSettings.push(fireSettings->SettingsData);
}
void UFireSystemFunctionLibrary::FireActorDelist (AActor* owner) {
	static TArray<UFireNodeComponent*> fireNodes = TArray<UFireNodeComponent*>();
	static UFireSettingsComponent* fireSettings = nullptr;
	if(getFireStuff(owner, &fireNodes, fireSettings) == false) {
		UIOFunctionLibrary::printErrorToScreen("FireActorOnDelist()'s owner doesn't have all fire components");
		return;
	}
	uint32 id = fireSettings->SettingsData.fireSystemID;
	if(fireSettings->SettingsData.isRegistered() == false) {
		UIOFunctionLibrary::printErrorToScreen("FireActorOnDelist()'s owner's fireSystemID is invalid");
		return;
	}
	uint32_t lastIndex = actorsWithFire.count-1;
	actorsWithFire[id] = actorsWithFire[lastIndex];
	actorsWithFire.pop();
	actorsFireSettings[id] = actorsFireSettings[lastIndex];
	actorsFireSettings.pop();
}

uint32_t fireSystemQueFinishedCount;
class QueableFireSystemTick: public IQueuedWork {
	uint32_t startIndex, endIndex;
public:
	void init(uint32_t _startIndex, uint32_t _endIndex) {
		startIndex = _startIndex;
		endIndex = _endIndex;
	}
	virtual ~QueableFireSystemTick() { }
	virtual void DoThreadedWork() {
		for(uint32_t i = startIndex; i < endIndex; i++) {
			AActor* owner = actorsWithFire[i];
			FireSettingsData fireSettings = actorsFireSettings[i];
			TArray<AActor*> overlappingActors;
			//owner->GetOverlappingActors(overlappingActors);
			TArray<AActor*> hitActors;
			getOverlappingActorsInRadius(owner, 25, hitActors);
		}
		fireSystemQueFinishedCount++;
	}
	virtual void Abandon() {
		
	}
};
FlatBuffer<QueableFireSystemTick, 32> queableFireSystemTicks;
void UFireSystemFunctionLibrary::FireSystemTick () {
	uint32_t count = actorsWithFire.count;
	int32 coreCount = FPlatformMisc::NumberOfCoresIncludingHyperthreads();
	uint32_t countPerThread = count/coreCount;
	uint32_t remainderCount = count%coreCount;
	fireSystemQueFinishedCount = 0;
	for(uint32_t i = 0; i < (uint32_t)coreCount; i++) {
		queableFireSystemTicks[i].init(i*countPerThread, i*countPerThread+countPerThread);
		GThreadPool->AddQueuedWork(&queableFireSystemTicks[i]);
	}
	waitForThreads:
	if(fireSystemQueFinishedCount == coreCount)
		goto endOfWait;
	goto waitForThreads;
	endOfWait:
	return;
}