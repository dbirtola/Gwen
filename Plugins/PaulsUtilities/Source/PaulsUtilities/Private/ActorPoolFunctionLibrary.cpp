// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorPoolFunctionLibrary.h"
#include "PooledActor.h"


TMap<FName, TArray<APooledActor*>> actorPool;

//APooledActor* UActorPoolFunctionLibrary::actorPoolGetActor(UClass* classType, AActor* instigator, const FTransform& transform) {
APooledActor* UActorPoolFunctionLibrary::actorPoolGetActor(UClass* classType, UWorld* world, const FTransform& transform) {
	FName name = classType->GetFName();
	if (actorPool.Contains(name) == true && actorPool[name].Num() != 0) {
		APooledActor* actor = actorPool[name].Pop(false);
		actor->initOnGet();
		return actor;
	}
	//spawn actor to return;
	//FActorSpawnParameters spawnInfo;
	//spawnInfo.Owner = instigator;
	FVector pos = transform.GetLocation();
	FRotator rot = transform.GetRotation().Rotator();
	//APooledActor* actor = Cast<APooledActor>(instigator->GetWorld()->SpawnActor(classType, &pos, &rot));
	APooledActor* actor = Cast<APooledActor>(world->SpawnActor(classType, &pos, &rot));
	actor->SetActorScale3D(transform.GetScale3D());
	actor->initOnGet();
	return actor;
}
void UActorPoolFunctionLibrary::actorPoolReturnActor(APooledActor* actor) {
	actor->resetOnReturn();
	FName actorName = actor->GetFName();
	if (actorPool.Contains(actorName) == false)
		actorPool.Add(actorName, TArray<APooledActor*>());
	actorPool[actorName].Add(actor);
}