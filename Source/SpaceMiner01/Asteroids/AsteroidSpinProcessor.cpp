
#include "MassCommonFragments.h" // For FTransformFragment
#include "AsteroidSpinProcessor.h"
#include "AsteroidFragments.h"
#include "MassExecutionContext.h"
#include "MassProcessor.h"
#include "../Mining/MiningTags.h"

UAsteroidSpinProcessor::UAsteroidSpinProcessor()
{
    // We want this to run during the main movement phase
    ExecutionOrder.ExecuteInGroup = FName("Movement");
    
   /* EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite);
    EntityQuery.AddRequirement<FAsteroidSpinFragment>(EMassFragmentAccess::ReadOnly);
    
    EntityQuery.AddTagRequirement<FAsteroidTag>(EMassFragmentPresence::All);

    // This is CRITICAL in 5.7
    EntityQuery.RegisterWithProcessor(*this);*/
}

void UAsteroidSpinProcessor::ConfigureQueries(const TSharedRef < FMassEntityManager > & EntityManager)
{
    // The engine calls this AFTER the object is initialized. No more crash!
    EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite);
    EntityQuery.AddRequirement<FAsteroidSpinFragment>(EMassFragmentAccess::ReadOnly);
    EntityQuery.AddTagRequirement<FAsteroidTag>(EMassFragmentPresence::All);
    
    // Tell the processor about this query
    EntityQuery.RegisterWithProcessor(*this);
}

void UAsteroidSpinProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
    // Iterate over the chunks of entities that match our query
    EntityQuery.ForEachEntityChunk(EntityManager, Context, [this](FMassExecutionContext& Context)
    {
        const int32 NumEntities = Context.GetNumEntities();
        
        // Get the arrays of data for this chunk (direct memory access)
        TArrayView<FTransformFragment> TransformList = Context.GetMutableFragmentView<FTransformFragment>();
        TConstArrayView<FAsteroidSpinFragment> SpinList = Context.GetFragmentView<FAsteroidSpinFragment>();
        
        const float DeltaTime = Context.GetDeltaTimeSeconds();

        for (int32 i = 0; i < NumEntities; ++i)
        {
            FTransform& Transform = TransformList[i].GetMutableTransform();
            const FAsteroidSpinFragment& Spin = SpinList[i];

            // Calculate new rotation
            FQuat CurrentRot = Transform.GetRotation();
            FQuat DeltaRot = FQuat(Spin.SpinAxis, FMath::DegreesToRadians(Spin.SpinSpeed * DeltaTime));
            
            Transform.SetRotation(DeltaRot * CurrentRot);
        }
    });
}