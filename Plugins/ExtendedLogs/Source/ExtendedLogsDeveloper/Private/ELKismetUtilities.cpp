// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#include "ELKismetUtilities.h"

#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"
#include "Misc/OutputDeviceError.h"

namespace ELKismetUtilities
{
bool GetLogCategoryNamePinDefaultValue(UEdGraphPin* Pin, FELLogCategoryName& OutValue)
{
	const auto pinDefaultValue = Pin->GetDefaultAsString();

	if (!pinDefaultValue.IsEmpty())
	{
		auto logCategoryStructType = FELLogCategoryName::StaticStruct();

		const auto buffer = logCategoryStructType->ImportText(*pinDefaultValue, &OutValue, nullptr, EPropertyPortFlags::PPF_SerializedAsImportText, GError, logCategoryStructType->GetName(), true);

		return buffer != nullptr;
	}
	return false;
}

bool SetLogCategoryNamePinDefaultValue(UEdGraphPin* Pin, const FELLogCategoryName& Value)
{
	if (Pin != nullptr)
	{
		FString exportLogCategory;
		FELLogCategoryName::StaticStruct()->ExportText(exportLogCategory, &Value, &Value, nullptr, EPropertyFlags::CPF_None, nullptr);

		if (Pin->GetDefaultAsString() != exportLogCategory)
		{
			Pin->GetSchema()->TrySetDefaultValue(*Pin, exportLogCategory);
		}
		return true;
	}
	return false;
}
} // namespace ELKismetUtilities