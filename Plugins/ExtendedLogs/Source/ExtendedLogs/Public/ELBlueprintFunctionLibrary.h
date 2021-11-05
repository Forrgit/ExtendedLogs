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
	/**
	 * Outputs the log message into the log file and output log window
	 * @param Message			Log message
	 * @param LogCategoryName	Log category name(must declared in editor plugin settings or in c++)
	 * @param LogVerbosity		Log verbosity levels are used to more easily control what is being printed
	 * @param bShowCallerName	Whether or not to add the name of the object that called the function			
	 * @param bPrintToScreen	Whether or not to print message to screen
	 * @param ScreenTextColor	Whether or not to print message to screen
	 * @param ScreenDuration	The display duration (if Print to Screen is True). Using negative number will result in loading the duration time from the config.
	 */
	UFUNCTION(BlueprintCallable, Category = "Extended Logs", meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "4"))
	static void Log(const FString& Message, FELLogCategoryName LogCategoryName, EELLogVerbosity LogVerbosity = EELLogVerbosity::Log, bool bShowCallerName = true, UObject* WorldContextObject = nullptr, bool bPrintToScreen = false, FLinearColor ScreenTextColor = FLinearColor(0.0, 0.66, 1.0), float ScreenDuration = 2.f);

	/**
	 * Outputs the log message into the log file and output log window.
	 * @param bCondition		Whether or not to log
	 * @param Message			Log message
	 * @param LogCategoryName	Log category name(must declared in editor plugin settings or in c++)
	 * @param LogVerbosity		Log verbosity levels are used to more easily control what is being printed
	 * @param bShowCallerName	Whether or not to add the name of the object that called the function			
	 * @param bPrintToScreen	Whether or not to print message to screen
	 * @param ScreenTextColor	Whether or not to print message to screen
	 * @param ScreenDuration	The display duration (if Print to Screen is True). Using negative number will result in loading the duration time from the config.
	 */
	UFUNCTION(BlueprintCallable, Category = "Extended Logs", meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "5"))
	static void ConditionalLog(bool bCondition, const FString& Message, FELLogCategoryName LogCategoryName, EELLogVerbosity LogVerbosity = EELLogVerbosity::Log, bool bShowCallerName = true, UObject* WorldContextObject = nullptr, bool bPrintToScreen = false, FLinearColor ScreenTextColor = FLinearColor(0.0, 0.66, 1.0), float ScreenDuration = 2.f);
};