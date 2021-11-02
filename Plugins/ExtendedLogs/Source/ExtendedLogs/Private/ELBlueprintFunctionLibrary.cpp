#include "ELBlueprintFunctionLibrary.h"

#include "ELExtendedLogsSettings.h"
#include "ELLogManager.h"

#include "ExtendedLogs.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Launch/Resources/Version.h"

void UELBlueprintFunctionLibrary::Log(const FString& Message, FELLogCategoryName LogCategoryName, EELLogVerbosity LogVerbosity, const UObject* WorldContextObject, bool bPrintToScreen, FLinearColor ScreenTextColor, float ScreenDuration)
{
	const auto nativeLogVerbosity = ConvertLogCategory(LogVerbosity);

	const auto settings = UELExtendedLogsSettings::Get();
	const auto logManager = FExtendedLogsModule::GetLogManager();

	if (logManager == nullptr
	    || (LogCategoryName.IsValid() && logManager->IsSuppressedLogCategory(LogCategoryName.Name, nativeLogVerbosity))
	    || (!settings->bAllowBPLogsOutputToEmptyOrInvalidCategories && logManager->FindLogCategory(LogCategoryName.Name).Num() == 0))
	{
		return;
	}

	FString messageSuffix;

#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 26) || ENGINE_MAJOR_VERSION > 4
	const FBlueprintContextTracker* blueprintExceptionTracker = FBlueprintContextTracker::TryGet();
	if (blueprintExceptionTracker != nullptr && blueprintExceptionTracker->GetScriptStack().Num() > 0)
	{
		const FFrame* lastFrame = blueprintExceptionTracker->GetScriptStack().Last();
		messageSuffix = lastFrame->GetStackDescription();
	}
#endif

	FMsg::Logf(nullptr, 0, LogCategoryName.Name, nativeLogVerbosity, TEXT("%s [%s]"), *Message, *messageSuffix);

	if (bPrintToScreen)
	{
		const auto printToScreenLogData = settings->PrintLogsToScreenVerbosityMap.Find(LogVerbosity);
		if (printToScreenLogData == nullptr || !printToScreenLogData->bPrintToScreen)
		{
			UKismetSystemLibrary::PrintString(WorldContextObject, FString::Printf(TEXT("%s [%s]"), *Message, *messageSuffix), true, false, ScreenTextColor, ScreenDuration);
		}
	}
}

void UELBlueprintFunctionLibrary::ConditionalLog(bool bCondition, const FString& Message, FELLogCategoryName LogCategoryName, EELLogVerbosity LogVerbosity, const UObject* WorldContextObject, bool bPrintToScreen, FLinearColor ScreenTextColor, float ScreenDuration)
{
	if (bCondition)
	{
		UELBlueprintFunctionLibrary::Log(Message, LogCategoryName, LogVerbosity, WorldContextObject, bPrintToScreen, ScreenTextColor, ScreenDuration);
	}
}
