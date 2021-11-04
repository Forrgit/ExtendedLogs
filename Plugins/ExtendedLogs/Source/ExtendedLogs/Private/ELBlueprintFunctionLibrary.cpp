// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#include "ELBlueprintFunctionLibrary.h"

#include "ELExtendedLogsSettings.h"
#include "ELLogManager.h"

#include "ExtendedLogs.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Launch/Resources/Version.h"

FString ELLogHelpers::GetFormattedScreenLog(const FString& Message, FName LogCategoryName, EELLogVerbosity LogVerbosity)
{
	FString messagePrefix = FString::Printf(TEXT("%s: "), *LogCategoryName.ToString());
	if (LogVerbosity != EELLogVerbosity::Log)
	{
		messagePrefix += FString::Printf(TEXT("%s: "), *GetVerbosityString(LogVerbosity));
	}
	return messagePrefix + Message;
}

FString ELLogHelpers::GetObjectName(const UObject* Object)
{
	return *GetNameSafe(Object);
}

FString ELLogHelpers::GetObjectName(const UActorComponent* Component)
{
	return Component != nullptr ? Component->GetReadableName() : FString();
}

void UELBlueprintFunctionLibrary::Log(const FString& Message, FELLogCategoryName LogCategoryName, EELLogVerbosity LogVerbosity, bool bShowCallerName, const UObject* WorldContextObject, bool bPrintToScreen, FLinearColor ScreenTextColor, float ScreenDuration)
{
	const auto nativeLogVerbosity = ConvertLogVerbosity(LogVerbosity);

	const auto settings = UELExtendedLogsSettings::Get();
	const auto logManager = FExtendedLogsModule::GetLogManager();

	if (logManager == nullptr || (LogCategoryName.IsValid() && logManager->IsSuppressedLogCategory(LogCategoryName.Name, nativeLogVerbosity)))
	{
		return;
	}

	FString callstackDescription;
	FString formattedCallerObjectName;

#if DO_BLUEPRINT_GUARD
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 26) || ENGINE_MAJOR_VERSION > 4
	const FBlueprintContextTracker* blueprintExceptionTracker = FBlueprintContextTracker::TryGet();
	if (blueprintExceptionTracker != nullptr && blueprintExceptionTracker->GetScriptStack().Num() > 0)
	{
		const FFrame* lastFrame = blueprintExceptionTracker->GetScriptStack().Last();
		callstackDescription = lastFrame->GetStackDescription();

		if (bShowCallerName)
		{
			formattedCallerObjectName = FString::Printf(TEXT("[%s] "), *ELLogHelpers ::GetObjectName(lastFrame->Object));
		}
	}
#endif

#endif //DO_BLUEPRINT_GUARD

	if (!LogCategoryName.IsValid() && !settings->bAllowEmptyLogCategory)
	{
		UE_LOG(LogExtendedLogs, Warning, TEXT("Detect empty log category in Log function from %s"), *callstackDescription);
	}
	else if (LogCategoryName.IsValid() && !settings->bAllowInvalidLogCategory && logManager->FindLogCategory(LogCategoryName.Name).Num() == 0)
	{
		UE_LOG(LogExtendedLogs, Warning, TEXT("Detect invalid log category in Log function from %s"), *callstackDescription);
	}

	FMsg::Logf(nullptr, 0, LogCategoryName.Name, nativeLogVerbosity, TEXT("%s%s (%s)"), *formattedCallerObjectName, *Message, *callstackDescription);

	if (bPrintToScreen)
	{
		const auto printToScreenLogData = settings->PrintLogsToScreenVerbosityMap.Find(LogVerbosity);
		if (printToScreenLogData == nullptr || !printToScreenLogData->bPrintToScreen)
		{
			UKismetSystemLibrary::PrintString(WorldContextObject, FString::Printf(TEXT("%s%s (%s)"), *formattedCallerObjectName, *ELLogHelpers::GetFormattedScreenLog(Message, LogCategoryName.Name, LogVerbosity), *callstackDescription), true, false, ScreenTextColor, ScreenDuration);
		}
	}
}

void UELBlueprintFunctionLibrary::ConditionalLog(bool bCondition, const FString& Message, FELLogCategoryName LogCategoryName, EELLogVerbosity LogVerbosity, bool bShowCallerName, const UObject* WorldContextObject, bool bPrintToScreen, FLinearColor ScreenTextColor, float ScreenDuration)
{
	if (bCondition)
	{
		UELBlueprintFunctionLibrary::Log(Message, LogCategoryName, LogVerbosity, bShowCallerName, WorldContextObject, bPrintToScreen, ScreenTextColor, ScreenDuration);
	}
}
