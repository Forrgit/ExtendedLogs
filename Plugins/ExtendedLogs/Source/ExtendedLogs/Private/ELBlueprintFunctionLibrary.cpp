#include "ELBlueprintFunctionLibrary.h"

#include "ELLogManager.h"

#include "ExtendedLogs.h"
#include "Runtime/Launch/Resources/Version.h"

void UELBlueprintFunctionLibrary::Log(const FString& Message, FELLogCategoryName LogCategoryName, EELLogVerbosity LogVerbosity)
{
	const auto logManager = FExtendedLogsModule::GetLogManager();
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

	FFrame::KismetExecutionMessage(TEXT("Invalid WorldContextObject. Cannot execute MiniTimer."), ELogVerbosity::Error);

	FMsg::Logf(nullptr, 0, LogCategoryName.Name, ConvertLogCategory(LogVerbosity), TEXT("%s [%s]"), *Message, *logSuffix);
}
