#include "ELExtendedLogsSettings.h"

UELExtendedLogsSettings::UELExtendedLogsSettings()
{
	CategoryName = "Plugins";
	SectionName = "Extended Logs Settings";
}

#if WITH_EDITOR
FText UELExtendedLogsSettings::GetSectionText() const
{
	return FText::FromName(SectionName);
}
#endif //WITH_EDITOR
