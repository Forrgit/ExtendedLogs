// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#include "ExtendedLogs.h"

#include "ELLogManager.h"
#include "Engine/Engine.h"

IMPLEMENT_MODULE(FExtendedLogsModule, ExtendedLogs)

void FExtendedLogsModule::StartupModule()
{
	LogManager.Reset(NewObject<UELLogManager>());
}

void FExtendedLogsModule::ShutdownModule()
{
	LogManager.Reset();
}

FExtendedLogsModule& FExtendedLogsModule::Get()
{
	return FModuleManager::LoadModuleChecked<FExtendedLogsModule>("ExtendedLogs");
}

UELLogManager* FExtendedLogsModule::GetLogManager() const
{
	return LogManager.Get();
}
