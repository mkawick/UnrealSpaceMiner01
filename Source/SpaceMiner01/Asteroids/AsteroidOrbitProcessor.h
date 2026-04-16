#pragma once

#include "MassProcessor.h"
#include "AsteroidOrbitProcessor.generated.h"

UCLASS()
class SPACEMINER01_API UAsteroidOrbitProcessor : public UMassProcessor
{
    GENERATED_BODY()

public:
    UAsteroidOrbitProcessor();

protected:
    virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;
    virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

private:
    FMassEntityQuery EntityQuery;
};