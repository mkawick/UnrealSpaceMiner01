// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityElementTypes.h"
#include "UObject/Object.h"
#include "RogueMassFragments.generated.h"

/**
 * 
 */
UCLASS()
class SPACEMINER01_API URogueMassFragments : public UObject
{
	GENERATED_BODY()
};

USTRUCT()
struct FRogueEntityFragment : public FMassFragment
{
	GENERATED_BODY()
	
	FVector Position;
	FVector Forward;
	float TimeToLive = 0.f;
};
