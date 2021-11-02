// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#include "ExtendedLogs.h"

#include "ELLogManager.h"
#include "ELOutputDeviceScreen.h"

#include "Engine/Engine.h"

IMPLEMENT_MODULE(FExtendedLogsModule, ExtendedLogs)

DEFINE_LOG_CATEGORY(LogExtendedLogs);

void FExtendedLogsModule::StartupModule()
{
	LogManager.Reset(NewObject<UELLogManager>());
	LogManager->InitializeManager();

	OutputDeviceScreen = MakeShared<FELOutputDeviceScreen>();

	if (GLog != nullptr)
	{
		GLog->AddOutputDevice(OutputDeviceScreen.Get());
	}
}

void FExtendedLogsModule::ShutdownModule()
{
	LogManager.Reset();

	if (GLog != nullptr && OutputDeviceScreen.IsValid())
	{
		GLog->RemoveOutputDevice(OutputDeviceScreen.Get());
	}
	OutputDeviceScreen.Reset();
}

UELLogManager* FExtendedLogsModule::GetLogManager()
{
	if (const auto module = FModuleManager::LoadModulePtr<FExtendedLogsModule>("ExtendedLogs"))
	{
		return module->LogManager.Get();
	}
	return nullptr;
}
