
#include "AsteroidOrbitProcessor.h"
#include "AsteroidFragments.h"
#include "MassCommonFragments.h"
#include "MassExecutionContext.h"

UAsteroidOrbitProcessor::UAsteroidOrbitProcessor()
{
    // We want this to run in the Movement group
    ExecutionOrder.ExecuteInGroup = FName("Movement");
}

void UAsteroidOrbitProcessor::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
    // We need both the Orbit data and the actual Transform (Position)
    EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite);
    EntityQuery.AddRequirement<FAsteroidOrbitFragment>(EMassFragmentAccess::ReadWrite);

    EntityQuery.RegisterWithProcessor(*this);
}

void UAsteroidOrbitProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
    EntityQuery.ForEachEntityChunk(EntityManager, Context, [](FMassExecutionContext& Context)
        {
            auto Transforms = Context.GetMutableFragmentView<FTransformFragment>();
            auto Orbits = Context.GetMutableFragmentView<FAsteroidOrbitFragment>();
            const float DeltaTime = Context.GetDeltaTimeSeconds();

            for (int32 i = 0; i < Context.GetNumEntities(); ++i)
            {
                FAsteroidOrbitFragment& Orbit = Orbits[i];
                FTransform& Transform = Transforms[i].GetMutableTransform();

                // 1. Advance the angle based on speed
                Orbit.CurrentAngle += Orbit.OrbitSpeed * DeltaTime;

                // 2. Calculate New Position relative to Center
                FVector NewLocation = Orbit.OrbitCenter;
                NewLocation.X += FMath::Cos(Orbit.CurrentAngle) * Orbit.OrbitRadius;
                NewLocation.Y += FMath::Sin(Orbit.CurrentAngle) * Orbit.OrbitRadius;

                // 3. Update the actual Entity in the world
                Transform.SetLocation(NewLocation);
            }
        });
}