// Fill out your copyright notice in the Description page of Project Settings.


#include "PooledActor.h"
#include "ActorPoolFunctionLibrary.h"

// Sets default values
APooledActor::APooledActor() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	FName typeName = GetFName();

}

// Called when the game starts or when spawned
void APooledActor::BeginPlay() {
	Super::BeginPlay();
}

void APooledActor::initOnGet() {
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);  //Probably should re enable this on booleon condition.
}

void APooledActor::resetOnReturn() {
	//DisableComponentsSimulatePhysics();
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

