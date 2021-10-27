#include "ELSLogCategoryGraphPin.h"

#include "ELLogCategory.h"
#include "ELSLogCategoryWidget.h"

void SELLogCategoryGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget> SELLogCategoryGraphPin::GetDefaultValueWidget()
{
	// clang-format off
	return SNew(SELLogCategoryWidget)
		.InitialItem(*GetParsedPinDefaultValue())
		.OnSelectionChanged_Raw(this, &SELLogCategoryGraphPin::OnSelectionChanged);
	// clang-format on
}

FString SELLogCategoryGraphPin::GetParsedPinDefaultValue() const
{
	const auto pinDefaultValue = GraphPinObj->GetDefaultAsString();

	FELLogCategory logCategory;

	if (!pinDefaultValue.IsEmpty())
	{
		auto logCategoryStructType = FELLogCategory::StaticStruct();
		logCategoryStructType->ImportText(*pinDefaultValue, &logCategory, nullptr, EPropertyPortFlags::PPF_SerializedAsImportText, GError, logCategoryStructType->GetName(), true);
	}
	return logCategory.Name.ToString();
}

void SELLogCategoryGraphPin::SetPinDefaultValue(const FString& Value)
{
	const FELLogCategory logCategory{ *Value };

	FString exportLogCategory;
	FELLogCategory::StaticStruct()->ExportText(exportLogCategory, &logCategory, &logCategory, nullptr, EPropertyFlags::CPF_None, nullptr);

	if (GraphPinObj->GetDefaultAsString() != exportLogCategory)
	{
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, exportLogCategory);
	}
}

void SELLogCategoryGraphPin::OnSelectionChanged(const FString& InItem)
{
	SetPinDefaultValue(InItem);
}
