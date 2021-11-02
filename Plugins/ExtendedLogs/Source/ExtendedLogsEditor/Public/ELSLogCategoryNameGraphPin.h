// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "SGraphPin.h"

class SELLogCategoryNameGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SELLogCategoryNameGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

	//~ Begin SGraphPin Interface
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;
	//~ End SGraphPin Interface

private:
	void OnSelectionChanged(const FString& InItem);
};
