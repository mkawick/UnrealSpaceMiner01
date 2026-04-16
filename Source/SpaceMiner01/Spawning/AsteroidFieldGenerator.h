#pragma once
// AsteroidFieldGenerator.h
#include "MassEntitySpawnDataGeneratorBase.h"
#include "MassEntityTypes.h"
#include "../Mining/SpaceMinerTypes.h"
#include "AsteroidFieldGenerator.generated.h"

UCLASS(BlueprintType, EditInlineNew)
class SPACEMINER01_API UAsteroidFieldGenerator : public UMassEntitySpawnDataGeneratorBase
{
    GENERATED_BODY()
public:
    virtual void Generate(UObject& QueryOwner,
        TConstArrayView<FMassSpawnedEntityType> EntityTypes,
        int32 Count,
        FFinishedGeneratingSpawnDataSignature& FinishedGeneratingSpawnPointsDelegate) const override;
    void GenerateMassEntitySettings() const;
};

