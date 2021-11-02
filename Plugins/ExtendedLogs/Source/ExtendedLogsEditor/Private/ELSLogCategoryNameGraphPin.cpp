#include "ELSLogCategoryNameGraphPin.h"

#include "ELKismetUtilities.h"
#include "ELSLogCategoryNameWidget.h"
#include "ELTypes.h"

void SELLogCategoryNameGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget> SELLogCategoryNameGraphPin::GetDefaultValueWidget()
{
	FELLogCategoryName defaultLogCategoryName;
	ELKismetUtilities::GetLogCategoryNamePinDefaultValue(GraphPinObj, defaultLogCategoryName);
	// clang-format off
	return SNew(SBox)
			.WidthOverride(170)
			[
				SNew(SELLogCategoryNameWidget)
				.InitialItem(defaultLogCategoryName.Name)
				.OnSelectionChanged_Raw(this, &SELLogCategoryNameGraphPin::OnSelectionChanged)			
			];

	// clang-format on
}

void SELLogCategoryNameGraphPin::OnSelectionChanged(const FString& InItem)
{
	ELKismetUtilities::SetLogCategoryNamePinDefaultValue(GraphPinObj, FELLogCategoryName(*InItem));
}
