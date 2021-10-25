#include "ELBlueprintFunctionLibrary.h"

void UELBlueprintFunctionLibrary::Log(const FString& Message, FELLogCategory LogCategory, EELLogVerbosity LogVerbosity)
{
	FMsg::Logf(nullptr, 0, *Message, static_cast<ELogVerbosity::Type>(LogVerbosity), TEXT("%s"), *Message);
}
