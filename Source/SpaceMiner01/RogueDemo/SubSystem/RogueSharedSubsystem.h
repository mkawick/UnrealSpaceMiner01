#pragma once

#include <CoreMinimal.h>
#include <MassProcessor.h> // Most Mass structs live here
#include <MassEntityTemplate.h>
#include "Subsystems/WorldSubsystem.h"
#include "RogueSharedSubsystem.generated.h"

struct FRogueSpawnRequest;
struct FMassEntityManager;
struct FMassEntityTemplate;
class UMassEntityConfigAsset;
class UMassSpawnerSubsystem;
/**
 * 
 */
UCLASS()
class SPACEMINER01_API URogueSharedSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	void EnqueueSpawnRequest(FRogueSpawnRequest&);

	void StartSpawnManager();
	void StopSpawnManager();
	
protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	void SpawnManager();
	void ProcessPendingSpawnRequests();
	void ConfigureSpawnedEntities(const FRogueSpawnRequest& spawnRequest, const TArray<FMassEntityHandle>& RequestEntitiesArray);
	void SpawnEntities();
	
	UPROPERTY()
	UMassEntityConfigAsset* EntityConfig;
	
	UPROPERTY()
	TArray<FRogueSpawnRequest> PendingRequests;
	
	UPROPERTY()
	UMassSpawnerSubsystem* SpawnerSubsystem;
	
	
private:
	FMassEntityManager* EntityManager;
	FMassEntityTemplate EntityTemplate;	
	FTimerHandle SpawnTimerHandle;
};
