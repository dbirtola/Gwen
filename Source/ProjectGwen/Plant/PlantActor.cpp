// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantActor.h"
#include "PlantFunctionLibrary.h"

void APlantActor::DelistSelf() {
	UPlantFunctionLibrary::PlantDelist(this);
}

// Sets default values
APlantActor::APlantActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlantActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlantActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

