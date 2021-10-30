// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "ELOutputDeviceScreen.h"

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "UObject/StrongObjectPtr.h"

class UELLogManager;

/**
* The public interface to this module
*/
class EXTENDEDLOGS_API FExtendedLogsModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static FExtendedLogsModule& Get();

	UELLogManager* GetLogManager() const;

private:
	TStrongObjectPtr<UELLogManager> LogManager;

	TUniquePtr<FELOutputDeviceScreen> OutputDeviceScreen;
};
