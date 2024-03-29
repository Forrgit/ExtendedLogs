// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "ELTypes.h"

#include "BlueprintNodeSignature.h"
#include "EdGraph/EdGraphNodeUtils.h"
#include "K2Node_CallFunction.h"

#include "ELK2Node_Log.generated.h"

UCLASS(meta = (Keywords = "Log"))
class UELK2Node_Log : public UK2Node_CallFunction
{
	GENERATED_BODY()
public:
	//~ Begin EdGraphNode Interface
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	//~ End EdGraphNode Interface

	//~ Begin UK2Node Interface
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;
	//~ End UK2Node Interface

	UEdGraphPin* GetLogCategoryPin() const;

protected:
	virtual void InitializeNode(FName InNativeFunctionName);

protected:
	UPROPERTY()
	FName NativeFunctionName;
	FELLogCategoryName TmpDefaultLogCategoryName;
};