// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "SSearchableComboBox.h"
#include "Widgets/Input/SCheckBox.h"

class SSearchableComboBox;

class EXTENDEDLOGSEDITOR_API SELLogCategoryNameWidget : public SComboButton
{
	using ListItemPtr = TSharedPtr<FString>;

	DECLARE_DELEGATE_OneParam(FOnSelectionChangedDelegate, const FString& /*ItemValue*/);

public:
	/** Type of list used for showing menu options. */
	using SComboListType = SListView<TSharedPtr<FString>>;

	SLATE_BEGIN_ARGS(SELLogCategoryNameWidget)
	{
	}

	SLATE_ARGUMENT(FName, InitialItem);
	SLATE_EVENT(FOnSelectionChangedDelegate, OnSelectionChanged);

	SLATE_END_ARGS()

	/**
	 * Construct the widget from a declaration
	 *
	 * @param InArgs   Declaration from which to construct the combo box
	 */
	void Construct(const FArguments& InArgs);

	void ClearSelection();
	void SetSelectedItem(TSharedPtr<FString> InSelectedItem);

	TSharedPtr<FString> GetSelectedItem();

	void RefreshOptions();

	FOnSelectionChangedDelegate& GetOnSelectionChanged();

private:
	/** Generate a row for the InItem in the combo box's list (passed in as OwnerTable). Do this by calling the user-specified OnGenerateWidget */
	TSharedRef<ITableRow> GenerateMenuItemRow(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable);

	/** Called if the menu is closed */
	void OnMenuOpenChanged(bool bOpen);

	/** Invoked when the selection in the list changes */
	void OnSelectionChanged_Internal(TSharedPtr<FString> ProposedSelection, ESelectInfo::Type SelectInfo);

	/** Invoked when the search text changes */
	void OnSearchTextChanged(const FText& ChangedText);

	/** Sets the current selection to the first valid match when user presses enter in the filter box */
	void OnSearchTextCommitted(const FText& InText, ETextCommit::Type InCommitType);

	/** Handle clicking on the content menu */
	FReply OnButtonClicked() override;

	void SetSelectedItemByValue(const FString& NewItem);

	FText GetCurrentSelection() const;

	FText GetTooltipText() const;

	void OnCheckBoxUseFilterStateChanged(ECheckBoxState State);

	void OnRegisterLogsEvent();
	void OnPluginSettingsChanged(class UObject*, struct FPropertyChangedEvent& PropertyChangedEvent);

private:
	/** The item currently selected in the combo box */
	TSharedPtr<FString> SelectedItem;
	/** The search field used for the combox box's contents */
	TSharedPtr<SEditableTextBox> SearchField;
	/** The ListView that we pop up; visualized the available options. */
	TSharedPtr<SComboListType> ComboListView;

	/** Updated whenever search text is changed */
	FText SearchText;

	/** Source data for this combo box */
	TArray<TSharedPtr<FString>> OptionsSource;

	FOnSelectionChangedDelegate OnSelectionChanged;

	TSharedPtr<SCheckBox> CheckBoxUseFilter;
};
