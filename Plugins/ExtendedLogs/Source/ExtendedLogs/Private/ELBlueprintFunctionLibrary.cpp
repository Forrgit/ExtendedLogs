#include "ELBlueprintFunctionLibrary.h"

#include "ELLogManager.h"

#include "ExtendedLogs.h"
#include "Runtime/Launch/Resources/Version.h"

void UELBlueprintFunctionLibrary::Log(const FString& Message, FELLogCategory LogCategoryName, EELLogVerbosity LogVerbosity)
{
	auto& logsModule = FExtendedLogsModule::Get();
	const auto logManager = logsModule.GetLogManager();
	if (logManager == nullptr || logManager->IsSuppressedLogCategory(LogCategoryName.Name, ConvertLogCategory(LogVerbosity)))
	{
		return;
	}

	FString logSuffix;

#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 26) || ENGINE_MAJOR_VERSION > 4
	const FBlueprintContextTracker* blueprintExceptionTracker = FBlueprintContextTracker::TryGet();
	if (blueprintExceptionTracker != nullptr && blueprintExceptionTracker->GetScriptStack().Num() > 0)
	{
		const FFrame* lastFrame = blueprintExceptionTracker->GetScriptStack().Last();
		logSuffix = GetNameSafe(lastFrame->Object);
	}
#endif

	FMsg::Logf(nullptr, 0, LogCategoryName.Name, ConvertLogCategory(LogVerbosity), TEXT("%s [%s]"), *Message, *logSuffix);
}
