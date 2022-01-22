// Fill out your copyright notice in the Description page of Project Settings.


#include "ECSEntityRefComponent.h"
#include "EntityObjectLoader.h"

DDECS<max_component_types, max_entities> ecs = DDECS<max_component_types, max_entities>();

ComponentID ownerComponentID = ecs.registerComponent("owner", sizeof(AActor*));

// Sets default values for this component's properties
UECSEntityRefComponent::UECSEntityRefComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UECSEntityRefComponent::getComponentDataFromFile(const FString& filePath) {
	if (entityID == -1) throw;
	FString fullPath = FPaths::ProjectContentDir() + "Data/";
	fullPath += filePath;
	FString dataFromFile;
	FFileHelper::LoadFileToString(dataFromFile, *fullPath);
	EntityObject entityObject = EntityObjectLoader::createEntityObjectFromString(TCHAR_TO_ANSI(*dataFromFile));

	// Transfer entityObject to ecs
	for (auto& c : entityObject.components) {
		void* data = c.data;
		ComponentID componentID = ecs.registerComponent(c.name, c.size);
		if (c.type == ComponentObject::TYPE::TYPE_ARRAY) {
			ecs.emplace(entityID, componentID, c.data);
			continue;
		}
		ecs.emplace(entityID, componentID, &c.data);
	}
}
void UECSEntityRefComponent::emplaceInt(int32 data, const FString& componentName) {
	ComponentID componentID = ecs.registerComponent(TCHAR_TO_UTF8 (*componentName), sizeof(int32));
	ecs.emplace(entityID, componentID, &data);
}


// Called when the game starts
void UECSEntityRefComponent::BeginPlay() {
	Super::BeginPlay();
	if (entityID != -1) throw;
	entityID = (int32)ecs.getNewEntity();
	AActor* owner = GetOwner();
	ecs.emplace(entityID, ownerComponentID, &owner);
}


// Called every frame
void UECSEntityRefComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

