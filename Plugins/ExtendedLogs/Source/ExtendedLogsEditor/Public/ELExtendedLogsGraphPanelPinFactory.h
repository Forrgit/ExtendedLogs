#pragma once

#include "CoreMinimal.h"
#include "ELLogCategory.h"
#include "ELSLogCategoryGraphPin.h"
#include "EdGraphSchema_K2.h"
#include "EdGraphUtilities.h"
#include "SGraphPin.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

class FELExtendedLogsGraphPanelPinFactory : public FGraphPanelPinFactory
{
	virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override
	{
		if (InPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
		{
			if (const UScriptStruct* pinStructType = Cast<UScriptStruct>(InPin->PinType.PinSubCategoryObject.Get()))
			{
				if (pinStructType->IsChildOf(FELLogCategory::StaticStruct()))
				{
					return SNew(SELLogCategoryGraphPin, InPin);
				}
			}
		}

		return nullptr;
	}
};
