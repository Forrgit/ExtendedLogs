#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "EdGraphUtilities.h"
#include "EdGraphSchema_K2.h"
#include "ELLogCategory.h"
#include "ELSLogCategoryGraphPin.h"
#include "SGraphPin.h"

class FELExtendedLogsGraphPanelPinFactory: public FGraphPanelPinFactory
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
