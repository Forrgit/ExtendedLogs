#include "ELBlueprintFunctionLibrary.h"

#include "Runtime/Launch/Resources/Version.h"

void UELBlueprintFunctionLibrary::Log(const FString& Message, FELLogCategory LogCategory, EELLogVerbosity LogVerbosity)
{
	FString bpFile;

#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 26) || ENGINE_MAJOR_VERSION > 4
	const FBlueprintContextTracker* blueprintExceptionTracker = FBlueprintContextTracker::TryGet();
	if (blueprintExceptionTracker != nullptr && blueprintExceptionTracker->GetScriptStack().Num() > 0)
	{
		const FFrame* lastFrame = blueprintExceptionTracker->GetScriptStack().Last();
		bpFile = GetNameSafe(lastFrame->Object);
	}
#endif

	FMsg::Logf(nullptr, 0, LogCategory.Name, static_cast<ELogVerbosity::Type>(LogVerbosity), TEXT("%s [%s]"), *Message, *bpFile);
}
