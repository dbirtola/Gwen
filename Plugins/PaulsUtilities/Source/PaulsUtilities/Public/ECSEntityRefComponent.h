// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <DDECS.h>
#include "ECSEntityRefComponent.generated.h"

constexpr uint32_t max_component_types = 64, max_entities = 100000;

extern DDECS<max_component_types, max_entities> ecs;
extern ComponentID ownerComponentID;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PAULSUTILITIES_API UECSEntityRefComponent : public UActorComponent {
	GENERATED_BODY()

	int32 entityID = -1;
public:	
	// Sets default values for this component's properties
	UECSEntityRefComponent();

	UFUNCTION(BlueprintCallable, Category = "PaulsUtilities|ECS")
	void getComponentDataFromFile(const FString& filePath);
	UFUNCTION(BlueprintCallable, Category = "PaulsUtilities|ECS")
	void emplaceInt(int32 data, const FString& componentName);

	int32 getEntityID() { return entityID; }

	void clean() {
		if (entityID == -1)
			throw;
		ecs.removeEntity(entityID);
		entityID = -1;
	}
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override {
		Super::EndPlay(EndPlayReason);
		if (entityID == -1)
			return;
		ecs.removeEntity(entityID);
		entityID = -1;
	}
	virtual void BeginDestroy() override {
		// NOTE:  This function is called at unexpected events such as the engine starting up.
		// So checking against -1 is necessary to avoid corruption.
		Super::BeginDestroy();
		if (entityID == -1)
			return;
		ecs.removeEntity(entityID);
		entityID = -1;
	}

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
