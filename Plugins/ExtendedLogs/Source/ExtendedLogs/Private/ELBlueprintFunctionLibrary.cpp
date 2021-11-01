#include "ELBlueprintFunctionLibrary.h"

#include "ELExtendedLogsSettings.h"
#include "ELLogManager.h"

#include "ExtendedLogs.h"
#include "Runtime/Launch/Resources/Version.h"

void UELBlueprintFunctionLibrary::Log(const FString& Message, FELLogCategoryName LogCategoryName, EELLogVerbosity LogVerbosity)
{
	const auto nativeLogVerbosity = ConvertLogCategory(LogVerbosity);

	const auto logManager = FExtendedLogsModule::GetLogManager();

	if (logManager == nullptr
	    || (LogCategoryName.IsValid() && logManager->IsSuppressedLogCategory(LogCategoryName.Name, nativeLogVerbosity))
	    || (!UELExtendedLogsSettings::Get()->bAllowBPLogsOutputToEmptyOrInvalidCategories && logManager->FindLogCategory(LogCategoryName.Name).Num() == 0))
	{
		return;
	}

	FString logSuffix;

#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 26) || ENGINE_MAJOR_VERSION > 4
	const FBlueprintContextTracker* blueprintExceptionTracker = FBlueprintContextTracker::TryGet();
	if (blueprintExceptionTracker != nullptr && blueprintExceptionTracker->GetScriptStack().Num() > 0)
	{
		const FFrame* lastFrame = blueprintExceptionTracker->GetScriptStack().Last();
		logSuffix = lastFrame->GetStackDescription();
	}
#endif

	FMsg::Logf(nullptr, 0, LogCategoryName.Name, nativeLogVerbosity, TEXT("%s [%s]"), *Message, *logSuffix);
}
