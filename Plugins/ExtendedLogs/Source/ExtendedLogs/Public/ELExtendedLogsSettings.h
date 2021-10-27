#pragma once

#include "Engine/DeveloperSettings.h"

#include "ELExtendedLogSettings.generated.h"

UCLASS(Config = Engine)
class EXTENDEDLOGS_API UELExtendedLogsSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UELExtendedLogsSettings();
	
	static const UELExtendedLogsSettings& Get()
	{
		return *GetDefault<UELExtendedLogsSettings>();
	}
	
public:
	UPROPERTY(EditAnywhere, Config)
	FString LogCategoryFilter;
};
