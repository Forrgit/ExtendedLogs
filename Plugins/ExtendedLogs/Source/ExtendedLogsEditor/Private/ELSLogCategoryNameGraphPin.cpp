// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

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
			.WidthOverride(190)
			.Visibility( this, &SGraphPin::GetDefaultValueVisibility )
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
