#include "ELLogVerbositySelectorCustomization.h"

#include "ELExtendedLogsSettings.h"
#include "ELLogManager.h"
#include "ELSLogCategoryNameWidget.h"

#include "DetailWidgetRow.h"
#include "ExtendedLogs.h"
#include "Misc/ConfigCacheIni.h"

static const FString ConfigLogSection = FString(TEXT("Core.Log"));

TSharedRef<IPropertyTypeCustomization> FELLogVerbosityCustomization::MakeInstance()
{
	return MakeShareable(new FELLogVerbosityCustomization());
}

void FELLogVerbosityCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	LogVerbosityPropertyHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FELLogVerbositySelector, LogVerbosity));
	check(LogVerbosityPropertyHandle.IsValid());

	LogVerbosityPropertyHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateSP(this, &FELLogVerbosityCustomization::OnLogVerbosityChanged));

	// clang-format off
	HeaderRow
	.NameContent()
	[
		//PropertyHandle->CreatePropertyNameWidget()
		SNew(SELLogCategoryNameWidget)
		.OnSelectionChanged_Raw(this, &FELLogVerbosityCustomization::OnLogCategoryChanged)
	]
	.ValueContent()
	[
		LogVerbosityPropertyHandle->CreatePropertyValueWidget()
	];
	// clang-format on
}

void FELLogVerbosityCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
}

EELLogVerbosity FELLogVerbosityCustomization::GetLogVerbosityPropertyValue() const
{
	void* rawValue;
	if (LogVerbosityPropertyHandle->GetValueData(rawValue) == FPropertyAccess::Success)
	{
		return *static_cast<decltype(FELLogVerbositySelector::LogVerbosity)*>(rawValue);
	}
	return EELLogVerbosity::NoLogging;
}

void FELLogVerbosityCustomization::OnLogCategoryChanged(const FString& Category)
{
	LogCategoryName = *Category;

	if (!Category.IsEmpty())
	{
		const auto logCategories = FExtendedLogsModule::GetLogManager()->FindLogCategory(LogCategoryName);
		if (logCategories.Num() != 0)
		{
			TArray<void*> rawData;
			LogVerbosityPropertyHandle->AccessRawData(rawData);
			if (rawData.Num() != 0)
			{
				EELLogVerbosity* logVerbosityPropertyValue = static_cast<EELLogVerbosity*>(rawData[0]);
				*logVerbosityPropertyValue = ConvertLogCategory(logCategories[0]->GetVerbosity());
			}
		}
	}
}

void FELLogVerbosityCustomization::OnLogVerbosityChanged()
{
	static const FString configFilePath = UELExtendedLogsSettings::Get()->GetDefaultConfigFilename();

	if (LogCategoryName != NAME_None)
	{
		auto settings = GetMutableDefault<UELExtendedLogsSettings>();

		if (const auto declaredLogCategory = settings->DeclaredLogCategories.Find(LogCategoryName))
		{
			*declaredLogCategory = GetLogVerbosityPropertyValue();
			settings->SaveConfig(CPF_Config, *configFilePath);
		}
		else
		{
			//Update ini file

			UEnum* enumClass = StaticEnum<EELLogVerbosity>();
			check(enumClass != nullptr);
			check(enumClass->GetCppForm() == UEnum::ECppForm::EnumClass);

			FString stringEnumValue = enumClass->GetNameStringByValue(static_cast<int32>(GetLogVerbosityPropertyValue()));
			stringEnumValue.RemoveFromStart(enumClass->CppType + TEXT("::"));

			GConfig->SetString(*ConfigLogSection, *LogCategoryName.ToString(), *stringEnumValue, settings->GetDefaultConfigFilename());

			//Update runtime data in logs
			const auto logManager = FExtendedLogsModule::GetLogManager();
			for (auto& logCategory : logManager->FindLogCategory(LogCategoryName))
			{
				logCategory->SetVerbosity(ConvertLogCategory(GetLogVerbosityPropertyValue()));
			}
		}

		GConfig->Flush(false, configFilePath);
	}
}