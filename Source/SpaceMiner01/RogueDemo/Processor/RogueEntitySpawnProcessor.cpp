// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceMiner01/RogueDemo/Processor/RogueEntitySpawnProcessor.h"
#include "MassCommonTypes.h"
#include "MassExecutionContext.h"
#include "SpaceMiner01/RogueDemo/Data/RogueMassFragments.h"

URogueEntitySpawnProcessor::URogueEntitySpawnProcessor() : EntityQuery(*this)
{
	ProcessingPhase = EMassProcessingPhase::PrePhysics;
	ExecutionOrder.ExecuteInGroup = UE::Mass::ProcessorGroupNames::Tasks;
}

void URogueEntitySpawnProcessor::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
	Super::ConfigureQueries(EntityManager);
	
	EntityQuery.AddRequirement<FRogueEntityFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.RegisterWithProcessor(*this);
}

void URogueEntitySpawnProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	Super::Execute(EntityManager, Context);
	
	EntityQuery.ForEachEntityChunk(Context, [&](FMassExecutionContext& SubContext)
	{
		//const TArrayView<FRogueEntityFragment> EntityFragments = SubContext.GetFragmentView<FRogueEntityFragment>();
		TArrayView<FRogueEntityFragment> MutEntityFragments = SubContext.GetMutableFragmentView<FRogueEntityFragment>();
		const int32 NumEntities = SubContext.GetNumEntities();
		int32 elapsedTime = SubContext.GetDeltaTimeSeconds();
		
		for (int i=0; i<NumEntities; i++)
		{
			auto& entityFragment = MutEntityFragments[i];
			auto entity = SubContext.GetEntity(i);
			
			entityFragment.TimeToLive -= elapsedTime;
			if (entityFragment.TimeToLive <= 0)
			{
				SubContext.Defer().DestroyEntity(entity);
			}
		}
		
		SubContext;
	});
}
