// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#include "ELSLogCategoryNameWidget.h"

#include "ELExtendedLogsSettings.h"
#include "ELLogManager.h"

#include "Algo/Find.h"
#include "ExtendedLogs.h"
#include "Internationalization/Regex.h"

void SELLogCategoryNameWidget::Construct(const FArguments& InArgs)
{
	const FText useFilterTooltip = FText::FromString(FString::Printf(TEXT("If true, the filter @%s from the %s in project settings is used"), GET_MEMBER_NAME_STRING_CHECKED(UELExtendedLogsSettings, LogCategoryWidgetFilter), *UELExtendedLogsSettings::StaticClass()->GetName()));

	OnSelectionChanged = InArgs._OnSelectionChanged;

	// clang-format off
	SSearchableComboBox::Construct(SSearchableComboBox::FArguments()
		.OptionsSource(&GlobalOptionsSource)
		.OnGenerateWidget_Raw(this, &SELLogCategoryNameWidget::OnGenerateWidgetForList)
		.OnSelectionChanged_Raw(this, &SELLogCategoryNameWidget::OnListSelectionChanged)
		.Content()
		[
			SNew(STextBlock)
			.Text_Raw(this, &SELLogCategoryNameWidget::GetCurrentSelection)
		]);

	TSharedRef<SWidget> newMenuContent =
		SNew(SBox)
		.WidthOverride(300.f)
		[
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
					.IsChecked(ECheckBoxState::Checked)
					.OnCheckStateChanged_Raw(this, &SELLogCategoryNameWidget::OnCheckBoxUseFilterStateChanged)
					.ToolTipText(useFilterTooltip)
				]
				+SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.AutoWidth()
				[
					SNew(STextBlock)
					.Text(FText::FromString(TEXT("Use default log category filter")))
					.ToolTipText(useFilterTooltip)
				]
				
			]
			+SVerticalBox::Slot()
			[
				MenuContent.ToSharedRef()
			]
		];
	// clang-format on

	SetMenuContent(newMenuContent);
	RefreshGlobalOptionSource();

	if (InArgs._InitialItem != NAME_None)
	{
		SetSelectedItem(FindItemInGlobalOptionSource(InArgs._InitialItem.ToString()));
		RefreshOptions();
	}

	if (const auto logManager = FExtendedLogsModule::GetLogManager())
	{
		logManager->OnRegisterLogsEvent.AddSP(this, &SELLogCategoryNameWidget::OnRegisterLogsEvent);
	}
	GetMutableDefault<UELExtendedLogsSettings>()->OnSettingChanged().AddSP(this, &SELLogCategoryNameWidget::OnPluginSettingsChanged);
}

SELLogCategoryNameWidget::FOnSelectionChangedDelegate& SELLogCategoryNameWidget::GetOnSelectionChanged()
{
	return OnSelectionChanged;
}

void SELLogCategoryNameWidget::RefreshGlobalOptionSource()
{
	const auto selectedItemValue = GetSelectedItem().IsValid() ? *GetSelectedItem() : FString();

	GlobalOptionsSource.Empty();

	if (const auto logManager = FExtendedLogsModule::GetLogManager())
	{
		const bool bUseFilter = CheckBoxUseFilter->IsChecked();

		for (const auto& logCategory : logManager->GetLogCategoriesNames())
		{
			const auto settings = UELExtendedLogsSettings::Get();
			if (!bUseFilter || settings->LogCategoryWidgetFilter.IsMatching(logCategory.ToString()))
			{
				GlobalOptionsSource.Add(MakeShareable(new FString(logCategory.ToString())));
			}
		}
	}

	GlobalOptionsSource.Sort([](auto& Lhs, auto& Rhs) {
		return *Lhs < *Rhs;
	});

	if (FindItemInGlobalOptionSource(selectedItemValue).IsValid())
	{
		SetSelectedItem(FindItemInGlobalOptionSource(selectedItemValue));
	}

	RefreshOptions();
}

TSharedPtr<FString> SELLogCategoryNameWidget::FindItemInGlobalOptionSource(const FString& ItemValue) const
{
	const auto foundItem = Algo::FindByPredicate(GlobalOptionsSource, [itemValue = ItemValue](ListItemPtr Item) {
		return *Item == itemValue;
	});

	return foundItem != nullptr ? *foundItem : nullptr;
}

FText SELLogCategoryNameWidget::GetCurrentSelection() const
{
	const auto selectedItem = const_cast<SELLogCategoryNameWidget*>(this)->GetSelectedItem();
	return FText::FromString(selectedItem.IsValid() ? *selectedItem : FString());
}

TSharedRef<SWidget> SELLogCategoryNameWidget::OnGenerateWidgetForList(ListItemPtr InItem) const
{
	return SNew(STextBlock).Text(FText::FromString(*InItem));
}

void SELLogCategoryNameWidget::OnListSelectionChanged(ListItemPtr InItem, ESelectInfo::Type InSelectInfo)
{
	SetSelectedItem(InItem);
	RefreshOptions();

	if (OnSelectionChanged.IsBound())
	{
		OnSelectionChanged.Execute(InItem.IsValid() ? *InItem : FString());
	}
}

void SELLogCategoryNameWidget::OnCheckBoxUseFilterStateChanged(ECheckBoxState State)
{
	RefreshGlobalOptionSource();
}

void SELLogCategoryNameWidget::OnRegisterLogsEvent()
{
	RefreshGlobalOptionSource();
}

void SELLogCategoryNameWidget::OnPluginSettingsChanged(UObject*, FPropertyChangedEvent& PropertyChangedEvent)
{
	RefreshGlobalOptionSource();
}
