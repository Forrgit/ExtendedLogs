#pragma once

#include "SGraphPin.h"

class SELLogCategoryGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SELLogCategoryGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

	//~ Begin SGraphPin Interface
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;
	//~ End SGraphPin Interface

private:
	FString GetParsedPinDefaultValue() const;
	void SetPinDefaultValue(const FString& Value);

	void OnSelectionChanged(const FString& InItem);
};
