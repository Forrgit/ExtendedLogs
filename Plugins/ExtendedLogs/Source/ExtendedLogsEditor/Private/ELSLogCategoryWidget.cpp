#include "ELSLogCategoryWidget.h"

#include "ELLogManager.h"
#include "ExtendedLogs.h"
#include "EditorWidgets/Public/SSearchableComboBox.h"

void SELLogCategoryWidget::Construct(const FArguments& InArgs)
{
	OnSelectionChanged = InArgs._OnSelectionChanged;

	ListItemPtr initialSelectedItem;
	
	if(const auto logManager = FExtendedLogsModule::Get().GetLogManager())
	{
		for(const auto& logCategory : logManager->GetLogCategories())
		{
			ListOptionsSource.Add(MakeShareable(new FString(logCategory.ToString())));
			if(logCategory == InArgs._InitialItem)
			{
				initialSelectedItem = ListOptionsSource.Last();
			}
		}
	}
	
	ChildSlot
	[
		SAssignNew(SearchableComboBox, SSearchableComboBox)
		.InitiallySelectedItem(initialSelectedItem)
		.OptionsSource(&ListOptionsSource)
		.OnGenerateWidget_Raw(this, &SELLogCategoryWidget::OnGenerateWidgetForList)
		.OnSelectionChanged_Raw(this, &SELLogCategoryWidget::OnListSelectionChanged)
	];
}

TSharedRef<SWidget> SELLogCategoryWidget::OnGenerateWidgetForList(ListItemPtr InItem) const
{
	return SNew(STextBlock).Text(FText::FromString(*InItem));
}

void SELLogCategoryWidget::OnListSelectionChanged(ListItemPtr InItem, ESelectInfo::Type InSelectInfo)
{
	SearchableComboBox->SetSelectedItem(InItem);

	if(OnSelectionChanged.IsBound())
	{
		FString string = *InItem.Get();
		OnSelectionChanged.Execute(InItem.IsValid() ? *string : FName());	
	}
	
}