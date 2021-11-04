// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#include "ELOutputDeviceScreen.h"

#include "ELBlueprintFunctionLibrary.h"
#include "ELExtendedLogsSettings.h"

#include "Engine/Engine.h"

#if WITH_EDITOR
#include "Editor.h"
#endif

FELOutputDeviceScreen::FELOutputDeviceScreen()
    : FOutputDevice()
{
#if WITH_EDITOR
	FEditorDelegates::EndPIE.AddLambda([this](bool) {
		if (UELExtendedLogsSettings::Get()->bClearScreenLogsOnEndPIE)
		{
			GEngine->ClearOnScreenDebugMessages();
		}
	});
#endif
}

FELOutputDeviceScreen::~FELOutputDeviceScreen()
{
#if WITH_EDITOR
	FEditorDelegates::EndPIE.RemoveAll(this);
#endif
}

void FELOutputDeviceScreen::Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category)
{
#if WITH_EDITOR
	if (GEditor != nullptr && !GEditor->IsPlayingSessionInEditor())
	{
		return;
	}
#endif

	const auto settings = Cast<UELExtendedLogsSettings>(UELExtendedLogsSettings::StaticClass()->GetDefaultObject(false));
	if (settings != nullptr && settings->bPrintLogsToScreen)
	{
		const auto printToScreenData = settings->PrintLogsToScreenVerbosityMap.Find(ConvertLogVerbosity(Verbosity));

		if (printToScreenData != nullptr && printToScreenData->bPrintToScreen && settings->ScreenLogCategoriesFilter.IsMatching(Category.ToString()))
		{
			GEngine->AddOnScreenDebugMessage(-1, printToScreenData->ScreenTime, printToScreenData->ScreenColor, ELLogHelpers::GetFormattedScreenLog(V, Category, ConvertLogVerbosity(Verbosity)));
		}
	}
}
