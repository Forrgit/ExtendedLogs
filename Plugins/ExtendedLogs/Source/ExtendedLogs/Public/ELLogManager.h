#pragma once

#include "UObject/Object.h"

#include "ELLogManager.generated.h"

UCLASS()
class EXTENDEDLOGS_API UELLogManager : public UObject
{
	GENERATED_BODY()
public:
	TArray<FName> GetLogCategories() const;
};
