#pragma once

#include "IPropertyTypeCustomization.h"

class SELLogCategoryWidget;

class FELLogCategoryCustomization : public IPropertyTypeCustomization
{
public:
	virtual ~FELLogCategoryCustomization() override;

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;

private:
	void OnLogNameValueChanged(const FString& NewValue);

private:
	TSharedPtr<SELLogCategoryWidget> LogCategoryWidget;

	TSharedPtr<IPropertyHandle> LogNamePropertyHandle;
};
