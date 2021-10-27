// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
* The public interface to this module
*/
class EXTENDEDLOGSEDITOR_API FExtendedLogsEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
