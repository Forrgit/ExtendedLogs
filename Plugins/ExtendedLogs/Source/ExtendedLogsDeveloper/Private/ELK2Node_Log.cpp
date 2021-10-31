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
}

FText UELK2Node_Log::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("Title", "Log");
}

FText UELK2Node_Log::GetTooltipText() const
{
	return LOCTEXT("Tooltip", "Outputs the log message into the log file and log widnow");
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
		UEdGraphPin* logCategoryNamePin = FindPinChecked(TEXT("LogCategoryName"));

		FELLogCategoryName logCategoryName;
		ELKismetUtilities::GetLogCategoryNamePinDefaultValue(logCategoryNamePin, logCategoryName);

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

FBlueprintNodeSignature UELK2Node_Log::GetSignature() const
{
	return Super::GetSignature();

	// FBlueprintNodeSignature NodeSignature = Super::GetSignature();
	// NodeSignature.AddKeyValue(LogCategoryName.Name.ToString());

	//	return NodeSignature;
}

void UELK2Node_Log::InitializeNode()
{
	SetFromFunction(UELBlueprintFunctionLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UELBlueprintFunctionLibrary, Log)));
}

#undef LOCTEXT_NAMESPACE
