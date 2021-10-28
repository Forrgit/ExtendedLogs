

#include "ELLogCategoryDetailsCustomization.h"

#include "ELLogCategory.h"
#include "ELSLogCategoryWidget.h"

#include "DetailWidgetRow.h"

FELLogCategoryCustomization::~FELLogCategoryCustomization()
{
	if (LogCategoryWidget.IsValid())
	{
		LogCategoryWidget->GetOnSelectionChanged().Unbind();
	}
}

TSharedRef<IPropertyTypeCustomization> FELLogCategoryCustomization::MakeInstance()
{
	return MakeShareable(new FELLogCategoryCustomization());
}

void FELLogCategoryCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	if (!PropertyHandle->IsValidHandle())
	{
		return;
	}

	LogNamePropertyHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FELLogCategory, Name));
	check(LogNamePropertyHandle.IsValid());

	FName logNameValue;
	LogNamePropertyHandle->GetValue(logNameValue);

	// clang-format off
	HeaderRow
	.NameContent()
	[
		PropertyHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	[
		SAssignNew(LogCategoryWidget, SELLogCategoryWidget)
		.InitialItem(logNameValue)
		.OnSelectionChanged_Raw(this, &FELLogCategoryCustomization::OnLogNameValueChanged)
	];
	// clang-format on
}

void FELLogCategoryCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
}

void FELLogCategoryCustomization::OnLogNameValueChanged(const FString& NewValue)
{
	LogNamePropertyHandle->SetValue(FName(*NewValue));
}
