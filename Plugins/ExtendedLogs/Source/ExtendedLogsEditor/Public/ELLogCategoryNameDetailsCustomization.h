#pragma once

#include "IPropertyTypeCustomization.h"

class SELLogCategoryNameWidget;

class FELLogCategoryNameCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;

private:
	void OnNameValueChanged(const FString& NewValue);

private:
	TSharedPtr<SELLogCategoryNameWidget> LogCategoryWidget;

	TSharedPtr<IPropertyHandle> NamePropertyHandle;
};
