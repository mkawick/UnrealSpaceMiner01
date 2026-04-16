// FInventoryFragment.h
#pragma once

#include "MassEntityTypes.h"
#include "../Mining/SpaceMinerTypes.h"
#include "FInventoryFragment.generated.h"

USTRUCT()
struct SPACEMINER01_API FInventoryFragment : public FMassFragment
{
    GENERATED_BODY()

    // A simple map of Mineral Type to Quantity
    // Note: Use TArray of structs if you need this to be visible in the Unreal Inspector easily
    UPROPERTY(EditAnywhere, Category = "Mining")
    float CopperStored = 0.f;

    UPROPERTY(EditAnywhere, Category = "Mining")
    float IronStored = 0.f;
};