#include "ELSLogCategoryNameGraphPin.h"

#include "ELSLogCategoryNameWidget.h"
#include "ELTypes.h"

void SELLogCategoryNameGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget> SELLogCategoryNameGraphPin::GetDefaultValueWidget()
{
	// clang-format off
	return SNew(SELLogCategoryNameWidget)
		.InitialItem(*GetParsedPinDefaultValue())
		.OnSelectionChanged_Raw(this, &SELLogCategoryNameGraphPin::OnSelectionChanged);
	// clang-format on
}

FString SELLogCategoryNameGraphPin::GetParsedPinDefaultValue() const
{
	const auto pinDefaultValue = GraphPinObj->GetDefaultAsString();

	FELLogCategoryName logCategory;

	if (!pinDefaultValue.IsEmpty())
	{
		auto logCategoryStructType = FELLogCategoryName::StaticStruct();
		logCategoryStructType->ImportText(*pinDefaultValue, &logCategory, nullptr, EPropertyPortFlags::PPF_SerializedAsImportText, GError, logCategoryStructType->GetName(), true);
	}
	return logCategory.Name.ToString();
}

void SELLogCategoryNameGraphPin::SetPinDefaultValue(const FString& Value)
{
	const FELLogCategoryName logCategory{ *Value };

	FString exportLogCategory;
	FELLogCategoryName::StaticStruct()->ExportText(exportLogCategory, &logCategory, &logCategory, nullptr, EPropertyFlags::CPF_None, nullptr);

	if (GraphPinObj->GetDefaultAsString() != exportLogCategory)
	{
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, exportLogCategory);
	}
}

void SELLogCategoryNameGraphPin::OnSelectionChanged(const FString& InItem)
{
	SetPinDefaultValue(InItem);
}
