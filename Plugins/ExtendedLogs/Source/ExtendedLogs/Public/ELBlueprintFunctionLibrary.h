// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "ELTypes.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "ELBlueprintFunctionLibrary.generated.h"

class UActorComponent;

namespace ELLogHelpers
{
FString GetFormattedScreenLog(const FString& Message, FName LogCategoryName, EELLogVerbosity LogVerbosity);

FString GetObjectName(const UObject* Object);
FString GetObjectName(const UActorComponent* Component);
} // namespace ELLogHelpers

UCLASS()
class EXTENDEDLOGS_API UELBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Extended Logs", meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "4"))
	static void Log(const FString& Message, FELLogCategoryName LogCategoryName, EELLogVerbosity LogVerbosity = EELLogVerbosity::Log, bool bShowCallerName = true, const UObject* WorldContextObject = nullptr, bool bPrintToScreen = false, FLinearColor ScreenTextColor = FLinearColor(0.0, 0.66, 1.0), float ScreenDuration = 2.f);

	UFUNCTION(BlueprintCallable, Category = "Extended Logs", meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "5"))
	static void ConditionalLog(bool bCondition, const FString& Message, FELLogCategoryName LogCategoryName, EELLogVerbosity LogVerbosity = EELLogVerbosity::Log, bool bShowCallerName = true, const UObject* WorldContextObject = nullptr, bool bPrintToScreen = false, FLinearColor ScreenTextColor = FLinearColor(0.0, 0.66, 1.0), float ScreenDuration = 2.f);
};