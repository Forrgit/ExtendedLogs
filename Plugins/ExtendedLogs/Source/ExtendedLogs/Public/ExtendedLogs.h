// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "UObject/StrongObjectPtr.h"

class UELLogManager;
class FELOutputDeviceScreen;

/*
 * ---Кастомные цвета логов
 * 
 * Валидация категорий логов в бп функции 
 * С++ логи с функцией и номером строки
 * ---Используемая категория лога по умолчанию
 * +++Не регистрировать пустые категории логов
 * Документация кода
 */

/**
* The public interface to this module
*/
class EXTENDEDLOGS_API FExtendedLogsModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static UELLogManager* GetLogManager();

private:
	TStrongObjectPtr<UELLogManager> LogManager;

	TSharedPtr<FELOutputDeviceScreen> OutputDeviceScreen;
};
