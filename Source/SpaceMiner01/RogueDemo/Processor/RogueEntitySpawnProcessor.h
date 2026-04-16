// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "RogueEntitySpawnProcessor.generated.h"

/**
 * 
 */
UCLASS()
class SPACEMINER01_API URogueEntitySpawnProcessor : public UMassProcessor
{
	GENERATED_BODY()
	
public:
	URogueEntitySpawnProcessor();
	
protected:
	virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context);
	
	FMassEntityQuery EntityQuery;
};
