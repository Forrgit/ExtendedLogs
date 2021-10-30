// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#include "ExtendedLogsEditor.h"

#include "ELExtendedLogsGraphPanelPinFactory.h"
#include "ELExtendedLogsSettings.h"
#include "ELLogCategoryNameDetailsCustomization.h"
#include "ELLogVerbositySelectorCustomization.h"

#include "Engine/Engine.h"

IMPLEMENT_MODULE(FExtendedLogsEditorModule, ExtendedLogsEditor)

void FExtendedLogsEditorModule::StartupModule()
{
	//Register custom pins
	TSharedPtr<FELExtendedLogsGraphPanelPinFactory> extendedLogsGraphPanelPinFactory = MakeShareable(new FELExtendedLogsGraphPanelPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(extendedLogsGraphPanelPinFactory);

	//Register custom property types details
	auto& propertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	propertyModule.RegisterCustomPropertyTypeLayout(*FELLogCategoryName::StaticStruct()->GetName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FELLogCategoryNameCustomization::MakeInstance));

	propertyModule.RegisterCustomPropertyTypeLayout(*FELLogVerbositySelector::StaticStruct()->GetName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FELLogVerbosityCustomization::MakeInstance));
}

void FExtendedLogsEditorModule::ShutdownModule()
{
}