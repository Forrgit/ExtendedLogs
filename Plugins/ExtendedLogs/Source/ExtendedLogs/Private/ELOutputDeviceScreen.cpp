#include "ELOutputDeviceScreen.h"

#include "ELExtendedLogsSettings.h"

#include "Engine/Engine.h"

void FELOutputDeviceScreen::Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category)
{
	if (const auto settings = UELExtendedLogsSettings::Get())
	{
		if (settings->bPrintLogsToScreen)
		{
			const auto printToScreenData = settings->PrintLogsToScreenVerbosityMap.Find(ConvertLogCategory(Verbosity));

			if (printToScreenData != nullptr && printToScreenData->bPrintToScreen && settings->ScreenLogCategoriesFilter.IsMatching(Category.ToString()))
			{
				GEngine->AddOnScreenDebugMessage(-1, printToScreenData->ScreenTime, printToScreenData->ScreenColor, V);
			}
		}
	}
}
