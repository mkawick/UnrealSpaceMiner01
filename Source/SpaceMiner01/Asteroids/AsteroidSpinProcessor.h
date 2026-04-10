#pragma once

#include "MassProcessor.h"
#include "AsteroidSpinProcessor.generated.h"

UCLASS()
class SPACEMINER01_API UAsteroidSpinProcessor : public UMassProcessor
{
    GENERATED_BODY()

public:
    UAsteroidSpinProcessor();

protected:
    // This is where we define what data we want to "look at"
    // Move requirements here
    	virtual void ConfigureQueries(const TSharedRef < FMassEntityManager > & EntityManager)   override;
    
    // This is where the actual math happens every frame
    virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

private:
    FMassEntityQuery EntityQuery;
};