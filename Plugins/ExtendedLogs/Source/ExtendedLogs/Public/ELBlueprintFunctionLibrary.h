#pragma once

#include "ELTypes.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "ELBlueprintFunctionLibrary.generated.h"

UCLASS()
class EXTENDEDLOGS_API UELBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintCallable, Category = "Extended logs", meta = (DisplayName = "UE LOG"))
	static void Log(const FString& Message, FELLogCategoryName LogCategoryName, EELLogVerbosity LogVerbosity);
};