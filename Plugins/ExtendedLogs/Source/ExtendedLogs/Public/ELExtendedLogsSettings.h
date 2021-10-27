#pragma once

#include "Engine/DeveloperSettings.h"

#include "ELExtendedLogsSettings.generated.h"

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
	/*
	 * Regular expression that is used to filter the categories of logs in the UELBlueprintFunctionLibrary::UE_LOG function
	 */
	UPROPERTY(EditAnywhere, Config)
	FString LogCategoryWidgetFilter;

	/*
	 * If true, use @LogCategoryWidgetFilter filter by default in the UELBlueprintFunctionLibrary::UE_LOG function
	 */
	UPROPERTY(EditAnywhere, Config)
	bool bUseLogCategoryWidgetFilterByDefault;

	/*
	 * If @bUseLogCategoryWidgetRegularExpression true, it replaces @LogCategoryWidgetFilter string filter
	 */
	UPROPERTY(EditAnywhere, Config, AdvancedDisplay)
	FString LogCategoryWidgetRegularExpression;

	/*
	* If true, use @LogCategoryWidgetRegularExpression instead @LogCategoryWidgetFilter string filter
	*/
	UPROPERTY(EditAnywhere, Config, AdvancedDisplay)
	bool bUseLogCategoryWidgetRegularExpression;
};
