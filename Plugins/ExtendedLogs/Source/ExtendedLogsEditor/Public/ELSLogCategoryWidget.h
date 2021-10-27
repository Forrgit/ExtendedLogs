#pragma once

#include "SSearchableComboBox.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/SCompoundWidget.h"

//SListViewSelectorDropdownMenu
//SListView

class SSearchableComboBox;

class SELLogCategoryWidget : public SSearchableComboBox
{
	using ListItemPtr = TSharedPtr<FString>;
	//using ListViewType = SListView<ListItemPtrType>;

	DECLARE_DELEGATE_OneParam(FOnSelectionChangedDelegate, const FString& /*ItemValue*/);

public:
	SLATE_BEGIN_ARGS(SELLogCategoryWidget)
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

protected:
	virtual void RefreshGlobalOptionSource();

	FText GetCurrentSelection() const;
	TSharedRef<SWidget> OnGenerateWidgetForList(ListItemPtr InItem) const;
	void OnListSelectionChanged(ListItemPtr InItem, ESelectInfo::Type InSelectInfo);

	void OnCheckBoxUseFilterStateChanged(ECheckBoxState State);

private:
	FOnSelectionChangedDelegate OnSelectionChanged;

	TSharedPtr<SCheckBox> CheckBoxUseFilter;

	//TSharedPtr<SSearchableComboBox> SearchableComboBox;
	TArray<ListItemPtr> GlobalOptionsSource;
};
