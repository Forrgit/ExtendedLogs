#pragma once

#include "Widgets/SCompoundWidget.h"

//SListViewSelectorDropdownMenu
//SListView

class SSearchableComboBox;

class SELLogCategoryWidget : public SCompoundWidget
{
	using ListItemPtr = TSharedPtr<FString>;
	//using ListViewType = SListView<ListItemPtrType>;

	DECLARE_DELEGATE_OneParam(FOnSelectionChangedDelegate, FString/*ItemValue*/);

public:
	SLATE_BEGIN_ARGS( SELLogCategoryWidget )
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

private:
	FText GetCurrentSelection() const;
	TSharedRef<SWidget> OnGenerateWidgetForList(ListItemPtr InItem) const;
	void OnListSelectionChanged(ListItemPtr InItem, ESelectInfo::Type InSelectInfo);
	
private:
	FOnSelectionChangedDelegate OnSelectionChanged;

	TSharedPtr<SSearchableComboBox> SearchableComboBox;  
	TArray<ListItemPtr> ListOptionsSource;
};

