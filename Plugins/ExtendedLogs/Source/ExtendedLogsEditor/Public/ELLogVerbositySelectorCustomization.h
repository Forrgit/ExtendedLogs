#pragma once

#include "ELTypes.h"

#include "IPropertyTypeCustomization.h"

class FELLogVerbosityCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;

private:
	EELLogVerbosity GetLogVerbosityPropertyValue() const;

	void OnLogCategoryChanged(const FString& Category);
	void OnLogVerbosityChanged();

private:
	TSharedPtr<IPropertyHandle> LogVerbosityPropertyHandle;
	FName LogCategoryName;
};
