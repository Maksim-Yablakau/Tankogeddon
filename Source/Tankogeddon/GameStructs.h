#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStructs.generated.h"

UENUM(BlueprintType)
enum class ECannonType : uint8
{
	FireProjectile = 0 UMETA(DisplayName = "Use Projectile"),
	FireTrace = 1 UMETA(DisplayName = "Use trace"),
};

UCLASS()
class TANKOGEDDON_API UGameStructs : public UObject
{
	GENERATED_BODY()
	
};
