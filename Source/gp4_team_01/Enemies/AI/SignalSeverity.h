#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ESignalSeverity : uint8 {
    Nonperceptible,
    Weak,
    Medium,
    Strong
};