#pragma once

#include "ELTypes.h"

#include "CoreMinimal.h"

#include "ELDeclarationLogCategoryInfo.generated.h"

USTRUCT(BlueprintType)
struct EXTENDEDLOGS_API FELDeclarationLogCategoryInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FName CategoryName;

	UPROPERTY(EditAnywhere)
	EELLogVerbosity Verbosity = EELLogVerbosity::Log;
};