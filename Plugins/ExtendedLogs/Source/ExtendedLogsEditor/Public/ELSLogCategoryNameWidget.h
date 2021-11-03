// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "SSearchableComboBox.h"
#include "Widgets/Input/SCheckBox.h"

class SSearchableComboBox;

class EXTENDEDLOGSEDITOR_API SELLogCategoryNameWidget : public SSearchableComboBox
{
	using ListItemPtr = TSharedPtr<FString>;

	DECLARE_DELEGATE_OneParam(FOnSelectionChangedDelegate, const FString& /*ItemValue*/);

public:
	SLATE_BEGIN_ARGS(SELLogCategoryNameWidget)
	{
	}

	SLATE_ARGUMENT(FName, InitialItem);
	SLATE_EVENT(FOnSelectionChangedDelegate, OnSelectionChanged);

	SLATE_END_ARGS()

	/**
	 * Construct the widget
	 *
	 * @param	InArgs			A declaration from which to construct the widget
	 * @param	InitOptions		Programmer-driven initialization options for this widget
	 */
	void Construct(const FArguments& InArgs);

	FOnSelectionChangedDelegate& GetOnSelectionChanged();

protected:
	virtual void RefreshGlobalOptionSource();
	TSharedPtr<FString> FindItemInGlobalOptionSource(const FString& ItemValue) const;

	FText GetCurrentSelection() const;
	TSharedRef<SWidget> OnGenerateWidgetForList(ListItemPtr InItem) const;
	void OnListSelectionChanged(ListItemPtr InItem, ESelectInfo::Type InSelectInfo);

	void OnCheckBoxUseFilterStateChanged(ECheckBoxState State);

	void OnRegisterLogsEvent();
	void OnPluginSettingsChanged(class UObject*, struct FPropertyChangedEvent& PropertyChangedEvent);

private:
	FOnSelectionChangedDelegate OnSelectionChanged;

	TSharedPtr<SCheckBox> CheckBoxUseFilter;

	TArray<ListItemPtr> GlobalOptionsSource;
};
