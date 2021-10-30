// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#include "ExtendedLogs.h"

#include "ELLogManager.h"
#include "ELOutputDeviceScreen.h"

#include "Engine/Engine.h"

IMPLEMENT_MODULE(FExtendedLogsModule, ExtendedLogs)

void FExtendedLogsModule::StartupModule()
{
	LogManager.Reset(NewObject<UELLogManager>());
	LogManager->InitializeManager();

	OutputDeviceScreen = MakeUnique<FELOutputDeviceScreen>();

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
}

FExtendedLogsModule& FExtendedLogsModule::Get()
{
	return FModuleManager::LoadModuleChecked<FExtendedLogsModule>("ExtendedLogs");
}

UELLogManager* FExtendedLogsModule::GetLogManager() const
{
	return LogManager.Get();
}
