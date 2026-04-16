// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueDemoDataTypes.generated.h"

UENUM()
enum class ERogueEntityType : uint8
{
	Entity
};

USTRUCT()
struct FRogueSpawnRequest
{
	GENERATED_BODY()
public:
	
	ERogueEntityType type = ERogueEntityType::Entity;
	int remainingCount = 0;
	FVector spawnPosition = FVector::ZeroVector;
	float TimeToLive = 10; 

};
