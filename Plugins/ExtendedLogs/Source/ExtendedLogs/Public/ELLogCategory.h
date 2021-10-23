#pragma once

#include "CoreMinimal.h"

#include "ELLogCategory.generated.h"

USTRUCT(BlueprintType)
struct EXTENDEDLOGS_API FELLogCategory
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FName Name;
};