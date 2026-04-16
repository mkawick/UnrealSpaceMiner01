// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueSharedSubsystem.h"

#include "MassCommonFragments.h"
#include "MassEntityConfigAsset.h"
#include "MassEntitySubsystem.h"
#include "MassSpawnerTypes.h"
#include "../Data/RogueDemoDeveloperSettings.h"
#include "Chaos/Character/CharacterGroundConstraintContainer.h"
#include "MassSpawnerSubsystem.h"
#include "Commandlets/AssetRegistryGenerator.h"
#include "SpaceMiner01/RogueDemo/Data/RogueDemoDataTypes.h"
#include "SpaceMiner01/RogueDemo/Data/RogueMassFragments.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ObjectMacros.h"

void URogueSharedSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	if (const auto* settings = GetDefault<URogueDemoDeveloperSettings>())
	{
		if (settings->EntityConfig.IsNull()) return;
		
		EntityConfig = settings->EntityConfig.LoadSynchronous();
	}
}

void URogueSharedSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void URogueSharedSubsystem::EnqueueSpawnRequest(FRogueSpawnRequest& request)
{
	PendingRequests.Add(request);
}

void URogueSharedSubsystem::StartSpawnManager()
{
	const auto& WorldContext = GetWorldRef();
	if (!IsValid(&WorldContext)) return;
	
	if (!WorldContext.GetTimerManager().IsTimerActive(SpawnTimerHandle))
	{
		WorldContext.GetTimerManager().SetTimer(SpawnTimerHandle, this, &ThisClass::SpawnManager, 0.1f, true);
	}
}

void URogueSharedSubsystem::StopSpawnManager()
{
	const auto& WorldContext = GetWorldRef();
	if (!IsValid(&WorldContext)) return;
	
	WorldContext.GetTimerManager().ClearTimer(SpawnTimerHandle);
}

void URogueSharedSubsystem::ProcessPendingSpawnRequests()
{
	if (!EntityManager || !SpawnerSubsystem) return;
	if (const auto* settings = GetDefault<URogueDemoDeveloperSettings>())
	{
		TArray<FMassEntityHandle> spawnedEntities;
		int spawnCountThisTick = settings->MaxSpawnPerTick;
		for (int i=PendingRequests.Num()-1; i>=0; --i)
		{
			FRogueSpawnRequest& request = PendingRequests[i];
			int countThisBatch = FMath::Min(spawnCountThisTick, request.remainingCount);
			if (countThisBatch == 0)
			{
				PendingRequests.RemoveAtSwap(i);
				continue;
			}
						
			FMassEntityTemplate RequestEntityTemplate;
			switch (request.type)
			{
			case ERogueEntityType::Entity:
				{
					RequestEntityTemplate = EntityTemplate;
				}
				break;
			}
			TArray<FMassEntityHandle> RequestEntitiesArray;
			SpawnerSubsystem->SpawnEntities(RequestEntityTemplate, countThisBatch, RequestEntitiesArray);
			
			ConfigureSpawnedEntities(request, RequestEntitiesArray);
			//const auto& WorldContext = GetWorldRef();
			
			request.remainingCount -= countThisBatch;
			spawnCountThisTick -= countThisBatch;
			
			if (request.remainingCount <= 0)
			{
				PendingRequests.RemoveAtSwap(i);
			}
			// return next frame
			if (spawnCountThisTick < 0)
			{
				return;
			}
		}
	}
}

void URogueSharedSubsystem::ConfigureSpawnedEntities(const FRogueSpawnRequest& SpawnRequest,
	const TArray<FMassEntityHandle>& RequestEntitiesArray)
{
	for (const auto& RequestEntity : RequestEntitiesArray)
	{
		if (FTransformFragment* tf = EntityManager->GetFragmentDataPtr<FTransformFragment>(RequestEntity))
		{
			// maybe scale and rotation as well
			tf->GetMutableTransform().SetLocation(SpawnRequest.spawnPosition);
		}
		switch(SpawnRequest.type)
		{
			case ERogueEntityType::Entity:
			{
				if (FRogueEntityFragment* ef = EntityManager->GetFragmentDataPtr<FRogueEntityFragment>(RequestEntity))
				{
					ef->TimeToLive = SpawnRequest.TimeToLive;
				}
			}
			break;
		}
	}
}

void URogueSharedSubsystem::SpawnEntities()
{
	// todo, calculate a position
	const auto& WorldContext = GetWorldRef();
	
	// Generate a spawn Request
	FRogueSpawnRequest SpawnRequest;
	SpawnRequest.type = ERogueEntityType::Entity;
	SpawnRequest.spawnPosition = FVector::ZeroVector;
	SpawnRequest.TimeToLive = 10.f;// 10 seconds
	SpawnRequest.remainingCount = 1;
	
	EnqueueSpawnRequest(SpawnRequest);
}


void URogueSharedSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	
	if (!EntityConfig) return;	
	EntityTemplate = EntityConfig->GetOrCreateEntityTemplate(InWorld);
	
	if(auto* EntitySub = InWorld.GetSubsystem<UMassEntitySubsystem>())
	{
		EntityManager = &EntitySub->GetMutableEntityManager();
	}
	
	SpawnerSubsystem = InWorld.GetSubsystem<UMassSpawnerSubsystem>();
	
	StartSpawnManager();
}

void URogueSharedSubsystem::SpawnManager()
{
	ProcessPendingSpawnRequests();
	SpawnEntities();
}

