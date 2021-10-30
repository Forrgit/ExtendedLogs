#pragma once

#include "ELLogCategory.h"

#include "CoreMinimal.h"

#include "ELDeclaredLog.generated.h"

USTRUCT(BlueprintType)
struct EXTENDEDLOGS_API FELDeclaredLogCategory
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FName CategoryName;

	UPROPERTY(EditAnywhere)
	EELLogVerbosity Verbosity;
};