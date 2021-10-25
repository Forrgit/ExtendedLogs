
#include "ELSLogCategoryGraphPin.h"

#include "ELSLogCategoryWidget.h"

void SELLogCategoryGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget> SELLogCategoryGraphPin::GetDefaultValueWidget()
{
	return SNew(SELLogCategoryWidget)
	.InitialItem(*GraphPinObj->GetDefaultAsString())
	.OnSelectionChanged_Raw(this, &SELLogCategoryGraphPin::OnSelectionChanged);
}

void SELLogCategoryGraphPin::OnSelectionChanged(FString InItem)
{
	GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, InItem);
}
