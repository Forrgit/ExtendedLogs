#include "ELLogCategoryNameDetailsCustomization.h"

#include "ELSLogCategoryNameWidget.h"
#include "ELTypes.h"

#include "DetailWidgetRow.h"

TSharedRef<IPropertyTypeCustomization> FELLogCategoryNameCustomization::MakeInstance()
{
	return MakeShareable(new FELLogCategoryNameCustomization());
}

void FELLogCategoryNameCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	if (!PropertyHandle->IsValidHandle())
	{
		return;
	}

	NamePropertyHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FELLogCategoryName, Name));
	check(NamePropertyHandle.IsValid());

	FName nameValue;
	NamePropertyHandle->GetValue(nameValue);

	// clang-format off
	HeaderRow
	.NameContent()
	[
		PropertyHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	[
		SAssignNew(LogCategoryWidget, SELLogCategoryNameWidget)
		.InitialItem(nameValue)
		.OnSelectionChanged(this, &FELLogCategoryNameCustomization::OnNameValueChanged)
	];
	// clang-format on
}

void FELLogCategoryNameCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
}

void FELLogCategoryNameCustomization::OnNameValueChanged(const FString& NewValue)
{
	NamePropertyHandle->SetValue(FName(*NewValue));
}
