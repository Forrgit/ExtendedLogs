#pragma once

#include "ELTypes.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "ELBlueprintFunctionLibrary.generated.h"

UCLASS()
class EXTENDEDLOGS_API UELBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Extended Logs", meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3"))
	static void Log(const FString& Message, FELLogCategoryName LogCategoryName, EELLogVerbosity LogVerbosity = EELLogVerbosity::Log, const UObject* WorldContextObject = nullptr, bool bPrintToScreen = false, FLinearColor ScreenTextColor = FLinearColor(0.0, 0.66, 1.0), float ScreenDuration = 2.f);

	UFUNCTION(BlueprintCallable, Category = "Extended Logs", meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "4"))
	static void ConditionalLog(bool bCondition, const FString& Message, FELLogCategoryName LogCategoryName, EELLogVerbosity LogVerbosity = EELLogVerbosity::Log, const UObject* WorldContextObject = nullptr, bool bPrintToScreen = false, FLinearColor ScreenTextColor = FLinearColor(0.0, 0.66, 1.0), float ScreenDuration = 2.f);
};