// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#include "ExtendedLogsEditor.h"

#include "ELExtendedLogsGraphPanelPinFactory.h"
#include "Engine/Engine.h"

IMPLEMENT_MODULE(FExtendedLogsEditorModule, ExtendedLogsEditor)


void FExtendedLogsEditorModule::StartupModule()
{
	TSharedPtr<FELExtendedLogsGraphPanelPinFactory> extendedLogsGraphPanelPinFactory = MakeShareable(new FELExtendedLogsGraphPanelPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(extendedLogsGraphPanelPinFactory);
}

void FExtendedLogsEditorModule::ShutdownModule()
{
}