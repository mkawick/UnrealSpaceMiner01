// SpaceMinerTypes.h
#pragma once

#include "CoreMinimal.h"
#include "SpaceMinerTypes.generated.h"

UENUM(BlueprintType)
enum class EMineralType : uint8
{
    None        UMETA(DisplayName = "None"),
    Copper      UMETA(DisplayName = "Copper"),
    Aluminum    UMETA(DisplayName = "Aluminum"),
    Rhodium     UMETA(DisplayName = "Rhodium"),
    Lithium     UMETA(DisplayName = "Lithium")
};