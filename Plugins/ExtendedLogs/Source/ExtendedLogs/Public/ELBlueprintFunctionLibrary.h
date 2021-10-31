#pragma once

#include "ELTypes.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "ELBlueprintFunctionLibrary.generated.h"

UCLASS()
class EXTENDEDLOGS_API UELBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//UFUNCTION(BlueprintCallable, Category = "Extended logs", meta = (DisplayName = "UE LOG"))
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static void Log(const FString& Message, FELLogCategoryName LogCategoryName, EELLogVerbosity LogVerbosity = EELLogVerbosity::Log);
};