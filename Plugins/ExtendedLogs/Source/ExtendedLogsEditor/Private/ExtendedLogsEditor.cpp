// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#include "ExtendedLogsEditor.h"

#include "ELExtendedLogsGraphPanelPinFactory.h"
#include "ELLogCategoryNameDetailsCustomization.h"

#include "Engine/Engine.h"

IMPLEMENT_MODULE(FExtendedLogsEditorModule, ExtendedLogsEditor)

void FExtendedLogsEditorModule::StartupModule()
{
	TSharedPtr<FELExtendedLogsGraphPanelPinFactory> extendedLogsGraphPanelPinFactory = MakeShareable(new FELExtendedLogsGraphPanelPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(extendedLogsGraphPanelPinFactory);

	auto& propertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	propertyModule.RegisterCustomPropertyTypeLayout("ELLogCategoryName", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FELLogCategoryNameCustomization::MakeInstance));
}

void FExtendedLogsEditorModule::ShutdownModule()
{
}