// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#include "ELSLogCategoryNameWidget.h"

#include "ELExtendedLogsSettings.h"
#include "ELLogManager.h"

#include "DetailLayoutBuilder.h"
#include "ExtendedLogs.h"
#include "Framework/Application/SlateUser.h"
#include "Internationalization/Regex.h"
#include "Styling/AppStyle.h"

#define LOCTEXT_NAMESPACE "SELLogCategoryNameWidget"

void SELLogCategoryNameWidget::Construct(const FArguments& InArgs)
{
	const FText useFilterTooltip = FText::FromString(FString::Printf(TEXT("If true, the filter @%s from the %s in project settings is used"), GET_MEMBER_NAME_STRING_CHECKED(UELExtendedLogsSettings, LogCategoryWidgetFilter), *UELExtendedLogsSettings::StaticClass()->GetName()));

	this->OnSelectionChanged = InArgs._OnSelectionChanged;

	// Work out which values we should use based on whether we were given an override, or should use the style's version
	const FComboBoxStyle* comboBoxStyle = &FCoreStyle::Get().GetWidgetStyle<FComboBoxStyle>("ComboBox");
	const FComboButtonStyle& ourComboButtonStyle = comboBoxStyle->ComboButtonStyle;

	const FButtonStyle* const ourButtonStyle = &ourComboButtonStyle.ButtonStyle;

	// clang-format off
	
	TSharedRef<SWidget> comboBoxMenuContent =
	
		SNew(SBox)
		.WidthOverride(300.f)
		.MaxDesiredHeight(330.0f)
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
			.AutoHeight()
			[
				SAssignNew(this->SearchField, SEditableTextBox)
				.Font(IDetailLayoutBuilder::GetDetailFont())
				.HintText(LOCTEXT("Search", "Search"))
				.OnTextChanged(this, &SELLogCategoryNameWidget::OnSearchTextChanged)
				.OnTextCommitted(this, &SELLogCategoryNameWidget::OnSearchTextCommitted)
			]
			+SVerticalBox::Slot()
			[
				SAssignNew(this->ComboListView, SComboListType)
			   .ListItemsSource(&OptionsSource)
			   .OnGenerateRow(this, &SELLogCategoryNameWidget::GenerateMenuItemRow)
			   .OnSelectionChanged(this, &SELLogCategoryNameWidget::OnSelectionChanged_Internal)
			   .SelectionMode(ESelectionMode::Single)
			]
		];

	// clang-format on

	// clang-format off
	
	// Set up content
	TSharedPtr<SWidget> buttonContent =
			SNew(STextBlock)
			.Text(this, &SELLogCategoryNameWidget::GetCurrentSelection);
	// clang-format on

	// clang-format off
	SComboButton::Construct(
	SComboButton::FArguments()
	        .ComboButtonStyle(&ourComboButtonStyle)
	        .ButtonStyle(ourButtonStyle)
	        //.Method(InArgs._Method)
	        .ButtonContent()
	        [
	            buttonContent.ToSharedRef()
	        ]
	        .MenuContent()
	        [
	            comboBoxMenuContent
	        ]
	        //.HasDownArrow(InArgs._HasDownArrow)
	        .ComboButtonStyle(FAppStyle::Get(), "SimpleComboButton")
			.ForegroundColor(FSlateColor::UseStyle())
	        .ContentPadding(FMargin(4.0, 2.0))
	        .OnMenuOpenChanged(this, &SELLogCategoryNameWidget::OnMenuOpenChanged)
	        .IsFocusable(true)
	        .ToolTipText(this, &SELLogCategoryNameWidget::GetTooltipText)
	        );

	// clang-format on

	SetMenuContentWidgetToFocus(SearchField);

	RefreshOptions();
	SetSelectedItemByValue(InArgs._InitialItem.ToString());

	if (const auto logManager = FExtendedLogsModule::GetLogManager())
	{
		logManager->OnRegisterLogsEvent.AddSP(this, &SELLogCategoryNameWidget::OnRegisterLogsEvent);
	}
	GetMutableDefault<UELExtendedLogsSettings>()->OnSettingChanged().AddSP(this, &SELLogCategoryNameWidget::OnPluginSettingsChanged);
}

void SELLogCategoryNameWidget::ClearSelection()
{
	ComboListView->ClearSelection();
}

void SELLogCategoryNameWidget::SetSelectedItem(TSharedPtr<FString> InSelectedItem)
{
	if (TListTypeTraits<TSharedPtr<FString>>::IsPtrValid(InSelectedItem))
	{
		ComboListView->SetSelection(InSelectedItem, ESelectInfo::OnNavigation);
	}
	else
	{
		ComboListView->SetSelection(SelectedItem, ESelectInfo::OnNavigation);
	}
}

TSharedPtr<FString> SELLogCategoryNameWidget::GetSelectedItem()
{
	return SelectedItem;
}

void SELLogCategoryNameWidget::RefreshOptions()
{
	const auto selectedItemValue = GetSelectedItem().IsValid() ? *GetSelectedItem() : FString();

	OptionsSource.Empty();

	if (const auto logManager = FExtendedLogsModule::GetLogManager())
	{
		const bool bUseFilter = CheckBoxUseFilter->IsChecked();
		const auto settings = UELExtendedLogsSettings::Get();

		for (const auto& logCategory : logManager->GetLogCategoriesNames())
		{
			const auto logCategoryString = logCategory.ToString();
			if ((SearchText.IsEmpty() || logCategoryString.Find(SearchText.ToString(), ESearchCase::Type::IgnoreCase) >= 0) //Check text filter
			    && (!bUseFilter || settings->LogCategoryWidgetFilter.IsMatching(logCategory.ToString()))) //Check settings filter
			{
				OptionsSource.Add(MakeShareable(new FString(logCategory.ToString())));
			}
		}
	}

	OptionsSource.Sort([](auto& Lhs, auto& Rhs) {
		return *Lhs < *Rhs;
	});

	ComboListView->RequestListRefresh();

	SetSelectedItemByValue(selectedItemValue);
}

TSharedRef<ITableRow> SELLogCategoryNameWidget::GenerateMenuItemRow(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable)
{
	return
	    // clang-format off
		SNew(SComboRow<TSharedPtr<FString>>, OwnerTable)
			.Style(&FCoreStyle::Get().GetWidgetStyle< FTableRowStyle >("TableView.Row"))
		    [
		    	SNew(STextBlock).Text(FText::FromString(*InItem))
		    ];
	// clang-format on
}

void SELLogCategoryNameWidget::OnMenuOpenChanged(bool bOpen)
{
	if (bOpen == false)
	{
		if (TListTypeTraits<TSharedPtr<FString>>::IsPtrValid(SelectedItem))
		{
			// Ensure the ListView selection is set back to the last committed selection
			ComboListView->SetSelection(SelectedItem, ESelectInfo::OnNavigation);
		}

		// Set focus back to ComboBox for users focusing the ListView that just closed
		TSharedRef<SWidget> ThisRef = AsShared();
		FSlateApplication::Get().ForEachUser([&ThisRef](FSlateUser& User) {
			if (User.HasFocusedDescendants(ThisRef))
			{
				User.SetFocus(ThisRef);
			}
		});
	}
}

void SELLogCategoryNameWidget::OnSelectionChanged_Internal(TSharedPtr<FString> ProposedSelection, ESelectInfo::Type SelectInfo)
{
	if (!ProposedSelection.IsValid())
	{
		//ComboListView->ScrollToBottom();
		return;
	}
	if (!SelectedItem.IsValid())
		ComboListView->RequestScrollIntoView(SelectedItem, 0);

	// Ensure that the proposed selection is different from selected
	if (ProposedSelection != SelectedItem)
	{
		SelectedItem = ProposedSelection;
		if (OnSelectionChanged.IsBound())
		{
			OnSelectionChanged.Execute(*ProposedSelection);
		}
	}

	// close combo as long as the selection wasn't from navigation
	if (SelectInfo != ESelectInfo::OnNavigation)
	{
		this->SetIsOpen(false);
	}
	else
	{
		ComboListView->RequestScrollIntoView(SelectedItem, 0);
	}
}

void SELLogCategoryNameWidget::OnSearchTextChanged(const FText& ChangedText)
{
	SearchText = ChangedText;

	RefreshOptions();
}

void SELLogCategoryNameWidget::OnSearchTextCommitted(const FText& InText, ETextCommit::Type InCommitType)
{
	if ((InCommitType == ETextCommit::Type::OnEnter) && OptionsSource.Num() > 0)
	{
		ComboListView->SetSelection(OptionsSource[0], ESelectInfo::OnKeyPress);
	}
}

FReply SELLogCategoryNameWidget::OnButtonClicked()
{
	// if user clicked to close the combo menu
	if (this->IsOpen())
	{
		// Re-select first selected item, just in case it was selected by navigation previously
		TArray<TSharedPtr<FString>> SelectedItems = ComboListView->GetSelectedItems();
		if (SelectedItems.Num() > 0)
		{
			OnSelectionChanged_Internal(SelectedItems[0], ESelectInfo::Direct);
		}
	}
	else
	{
		SearchField->SetText(FText::GetEmpty());
	}

	return SComboButton::OnButtonClicked();
}

SELLogCategoryNameWidget::FOnSelectionChangedDelegate& SELLogCategoryNameWidget::GetOnSelectionChanged()
{
	return OnSelectionChanged;
}

void SELLogCategoryNameWidget::SetSelectedItemByValue(const FString& NewItem)
{
	if (!NewItem.IsEmpty() && (!GetSelectedItem().IsValid() || *GetSelectedItem() != NewItem))
	{
		SetSelectedItem(MakeShared<FString>(NewItem));

		ComboListView->RequestListRefresh();
	}
}

FText SELLogCategoryNameWidget::GetCurrentSelection() const
{
	const auto selectedItem = const_cast<SELLogCategoryNameWidget*>(this)->GetSelectedItem();
	return FText::FromString(selectedItem.IsValid() ? *selectedItem : FString());
}

FText SELLogCategoryNameWidget::GetTooltipText() const
{
	return SelectedItem.IsValid() ? FText::FromString(*SelectedItem.Get()) : FText();
}

void SELLogCategoryNameWidget::OnCheckBoxUseFilterStateChanged(ECheckBoxState State)
{
	RefreshOptions();
}

void SELLogCategoryNameWidget::OnRegisterLogsEvent()
{
	RefreshOptions();
}

void SELLogCategoryNameWidget::OnPluginSettingsChanged(UObject*, FPropertyChangedEvent& PropertyChangedEvent)
{
	RefreshOptions();
}
