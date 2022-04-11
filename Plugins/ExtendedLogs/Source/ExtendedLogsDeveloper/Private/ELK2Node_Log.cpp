// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#include "ELK2Node_Log.h"

#include "ELBlueprintFunctionLibrary.h"
#include "ELExtendedLogsSettings.h"
#include "ELKismetUtilities.h"
#include "ELLogManager.h"

#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "ExtendedLogs.h"
#include "Kismet2/CompilerResultsLog.h"

#define LOCTEXT_NAMESPACE "UELK2Node_Log"

void UELK2Node_Log::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	if (TmpDefaultLogCategoryName.IsValid())
	{
		ELKismetUtilities::SetLogCategoryNamePinDefaultValue(GetLogCategoryPin(), TmpDefaultLogCategoryName);
	}
}

FText UELK2Node_Log::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(NativeFunctionName.ToString());
}

FLinearColor UELK2Node_Log::GetNodeTitleColor() const
{
	return FLinearColor(0.2f, 0.66f, 0.8f, 1.f);
}

void UELK2Node_Log::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	auto customizeNodeLambda = [](UEdGraphNode* NewNode, bool bIsTemplateNode, FName InNativeFunctionName) {
		auto logNode = CastChecked<UELK2Node_Log>(NewNode);
		logNode->InitializeNode(InNativeFunctionName);
	};

	UClass* ActionKey = GetClass();

	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		TArray<FName> nativeFunctionNames;
		nativeFunctionNames.Add(GET_FUNCTION_NAME_CHECKED(UELBlueprintFunctionLibrary, Log));
		nativeFunctionNames.Add(GET_FUNCTION_NAME_CHECKED(UELBlueprintFunctionLibrary, ConditionalLog));

		for (auto& nativeFunctionName : nativeFunctionNames)
		{
			UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
			check(NodeSpawner != nullptr);

			NodeSpawner->CustomizeNodeDelegate = UBlueprintNodeSpawner::FCustomizeNodeDelegate::CreateStatic(customizeNodeLambda, nativeFunctionName);
			ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
		}
	}
}

void UELK2Node_Log::ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const
{
	Super::ValidateNodeDuringCompilation(MessageLog);

	const auto logCategoryPin = GetLogCategoryPin();

	if (!logCategoryPin->HasAnyConnections())
	{
		FELLogCategoryName logCategoryName;
		ELKismetUtilities::GetLogCategoryNamePinDefaultValue(logCategoryPin, logCategoryName);

		const auto settings = UELExtendedLogsSettings::Get();

		if (!settings->bAllowEmptyLogCategory && !logCategoryName.IsValid())
		{
			MessageLog.Warning(*FText::FromString(TEXT("Missing log category name for @@")).ToString(), this);
		}
		else if (!settings->bAllowInvalidLogCategory && FExtendedLogsModule::GetLogManager()->FindLogCategory(logCategoryName.Name).Num() == 0)
		{
			MessageLog.Warning(*FText::Format(NSLOCTEXT("KismetCompiler", "InvalidLogCategoryName_WarningFmt", "Log category '{0}' not found, it category might have been removed,  @@"), FText::FromString(logCategoryName.Name.ToString())).ToString(), this);
		}
	}
}

UEdGraphPin* UELK2Node_Log::GetLogCategoryPin() const
{
	return FindPinChecked(TEXT("LogCategoryName"));
}

void UELK2Node_Log::InitializeNode(FName InNativeFunctionName)
{
	TmpDefaultLogCategoryName = UELExtendedLogsSettings::Get()->FunctionDefaultLogCategory;
	NativeFunctionName = InNativeFunctionName;
	SetFromFunction(UELBlueprintFunctionLibrary::StaticClass()->FindFunctionByName(InNativeFunctionName));
}

#undef LOCTEXT_NAMESPACE
