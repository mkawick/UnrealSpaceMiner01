// AsteroidFragments.h
#pragma once

#include "MassEntityTypes.h"
#include "../Mining/SpaceMinerTypes.h"
#include "AsteroidFragments.generated.h"

// 1. Fragment for the rotational movement
USTRUCT()
struct SPACEMINER01_API FAsteroidSpinFragment : public FMassFragment
{
    GENERATED_BODY()

    // The axis around which the asteroid spins
    UPROPERTY(EditAnywhere, Category = "Mass")
    FVector SpinAxis = FVector::UpVector;

    // Degrees per second
    UPROPERTY(EditAnywhere, Category = "Mass")
    float SpinSpeed = 10.0f;
};

// 2. Fragment for the mineral content and "health"
USTRUCT()
struct SPACEMINER01_API FMineralFragment : public FMassFragment
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Mass")
    EMineralType MineralType = EMineralType::Copper;

    // How many "hits" or how much laser energy before an orb pops out
    UPROPERTY(EditAnywhere, Category = "Mass")
    float Health = 100.0f;

    // Total minerals remaining in this rock
    UPROPERTY(EditAnywhere, Category = "Mass")
    int32 MineralCount = 50;
};

USTRUCT()
struct SPACEMINER01_API FAsteroidOrbitFragment : public FMassFragment
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Orbit")
    FVector OrbitCenter = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, Category = "Orbit")
    float OrbitRadius = 5000.f;

    UPROPERTY(EditAnywhere, Category = "Orbit")
    float OrbitSpeed = 0.2f; // Radians per second

    UPROPERTY(EditAnywhere, Category = "Orbit")
    float CurrentAngle = 0.f;
};