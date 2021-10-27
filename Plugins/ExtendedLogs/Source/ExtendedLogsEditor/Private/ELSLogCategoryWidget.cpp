#include "ELSLogCategoryWidget.h"

#include "ELExtendedLogSettings.h"
#include "ELLogManager.h"

#include "ExtendedLogs.h"
#include "Internationalization/Regex.h"

void SELLogCategoryWidget::Construct(const FArguments& InArgs)
{
	OnSelectionChanged = InArgs._OnSelectionChanged;

	ListItemPtr initialSelectedItem;

	// clang-format off
	SSearchableComboBox::Construct(SSearchableComboBox::FArguments()
		.InitiallySelectedItem(initialSelectedItem)
		.OptionsSource(&GlobalOptionsSource)
		.OnGenerateWidget_Raw(this, &SELLogCategoryWidget::OnGenerateWidgetForList)
		.OnSelectionChanged_Raw(this, &SELLogCategoryWidget::OnListSelectionChanged)
		.Content()
		[
			SNew(STextBlock)
			.Text_Raw(this, &SELLogCategoryWidget::GetCurrentSelection)
		]);

	TSharedRef<SWidget> newMenuContent =
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.AutoWidth()
			[
				SAssignNew(CheckBoxUseFilter, SCheckBox)
				.IsChecked(ECheckBoxState::Unchecked)
				.OnCheckStateChanged_Raw(this, &SELLogCategoryWidget::OnCheckBoxUseFilterStateChanged)
			]
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.AutoWidth()
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("Use filter")))
			]
		]
		+SVerticalBox::Slot()
		[
			MenuContent.ToSharedRef()
		];

	// clang-format on
	SetMenuContent(newMenuContent);

	RefreshGlobalOptionSource();
}

void SELLogCategoryWidget::RefreshGlobalOptionSource()
{
	GlobalOptionsSource.Empty();

	if (const auto logManager = FExtendedLogsModule::Get().GetLogManager())
	{
		const bool bUseFilter = CheckBoxUseFilter->IsChecked();
		const FRegexPattern filterRegexPattern(UELExtendedLogsSettings::Get().LogCategoryFilter);

		for (const auto& logCategory : logManager->GetLogCategories())
		{
			bool bMustAdd = true;
			if (bUseFilter)
			{
				FRegexMatcher matcher(filterRegexPattern, logCategory.ToString());
				bMustAdd = matcher.FindNext();
			}

			if (bMustAdd)
			{
				GlobalOptionsSource.Add(MakeShareable(new FString(logCategory.ToString())));
			}
		}
	}

	RefreshOptions();
}

FText SELLogCategoryWidget::GetCurrentSelection() const
{
	const auto selectedItem = const_cast<SELLogCategoryWidget*>(this)->GetSelectedItem();
	return FText::FromString(selectedItem.IsValid() ? *selectedItem : FString());
}

TSharedRef<SWidget> SELLogCategoryWidget::OnGenerateWidgetForList(ListItemPtr InItem) const
{
	return SNew(STextBlock).Text(FText::FromString(*InItem));
}

void SELLogCategoryWidget::OnListSelectionChanged(ListItemPtr InItem, ESelectInfo::Type InSelectInfo)
{
	SetSelectedItem(InItem);
	RefreshOptions();

	if (OnSelectionChanged.IsBound())
	{
		OnSelectionChanged.Execute(InItem.IsValid() ? *InItem : FString());
	}
}

void SELLogCategoryWidget::OnCheckBoxUseFilterStateChanged(ECheckBoxState State)
{
	RefreshGlobalOptionSource();
}