#include "ELExtendedLogsSettings.h"

#include "Internationalization/Regex.h"

FELPrintToScreenLogData::FELPrintToScreenLogData(bool bInPrintToScreen, float InScreenTime, FColor InScreenColor)
    : bPrintToScreen(bInPrintToScreen), ScreenTime(InScreenTime), ScreenColor(InScreenColor)
{
}

bool FELStringFilter::IsMatching(const FString& String) const
{
	if (bUseFilterAsRegularExpression)
	{
		const FRegexPattern filterRegexPattern(Filter);
		FRegexMatcher matcher(filterRegexPattern, String);
		return matcher.FindNext();
	}

	return Filter.IsEmpty() || String.Find(Filter, ESearchCase::Type::IgnoreCase) >= 0;
}

UELExtendedLogsSettings::UELExtendedLogsSettings()
{
	CategoryName = "Plugins";
	SectionName = "Extended Logs Settings";

	PrintLogsToScreenVerbosityMap.Add(EELLogVerbosity::Error, FELPrintToScreenLogData(true, 10.f, FColor::Red));
	PrintLogsToScreenVerbosityMap.Add(EELLogVerbosity::Warning, FELPrintToScreenLogData(true, 10.f, FColor::Yellow));
}

#if WITH_EDITOR
FText UELExtendedLogsSettings::GetSectionText() const
{
	return FText::FromName(SectionName);
}
#endif //WITH_EDITOR
