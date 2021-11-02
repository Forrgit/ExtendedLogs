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
	return LOCTEXT("Title", "Log");
}

FText UELK2Node_Log::GetTooltipText() const
{
	return LOCTEXT("Tooltip", "Outputs the log message into the log file and log widnow");
}

FLinearColor UELK2Node_Log::GetNodeTitleColor() const
{
	return FLinearColor(0.2f, 0.66f, 0.8f, 1.f);
}

void UELK2Node_Log::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	auto customizeNodeLambda = [](UEdGraphNode* NewNode, bool bIsTemplateNode) {
		auto logNode = CastChecked<UELK2Node_Log>(NewNode);
		logNode->InitializeNode();
	};

	UClass* ActionKey = GetClass();

	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		NodeSpawner->CustomizeNodeDelegate = UBlueprintNodeSpawner::FCustomizeNodeDelegate::CreateStatic(customizeNodeLambda);
		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

void UELK2Node_Log::ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const
{
	Super::ValidateNodeDuringCompilation(MessageLog);

	if (UELExtendedLogsSettings::Get()->bWarnIfLogCategoryIsEmpty)
	{
		FELLogCategoryName logCategoryName;
		ELKismetUtilities::GetLogCategoryNamePinDefaultValue(GetLogCategoryPin(), logCategoryName);

		const auto settings = UELExtendedLogsSettings::Get();

		if (settings->bWarnIfLogCategoryIsEmpty && !logCategoryName.IsValid())
		{
			MessageLog.Warning(*FText::FromString(TEXT("Missing log category name for @@")).ToString(), this);
		}
		else if (settings->bWarnIfLogCategoryInvalid && FExtendedLogsModule::GetLogManager()->FindLogCategory(logCategoryName.Name).Num() == 0)
		{
			MessageLog.Warning(*FText::Format(NSLOCTEXT("KismetCompiler", "InvalidLogCategoryName_WarningFmt", "Log category name '{0}' invalid or no longer exist for @@"), FText::FromString(logCategoryName.Name.ToString())).ToString(), this);
		}
	}
}

UEdGraphPin* UELK2Node_Log::GetLogCategoryPin() const
{
	return FindPinChecked(TEXT("LogCategoryName"));
}

void UELK2Node_Log::InitializeNode()
{
	TmpDefaultLogCategoryName = UELExtendedLogsSettings::Get()->FunctionDefaultLogCategory;
	SetFromFunction(UELBlueprintFunctionLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UELBlueprintFunctionLibrary, Log)));
}

#undef LOCTEXT_NAMESPACE
