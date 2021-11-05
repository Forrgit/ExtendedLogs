// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "ELTypes.h"
#include "Engine/DeveloperSettings.h"

#include "ELExtendedLogsSettings.generated.h"

USTRUCT(BlueprintType)
struct EXTENDEDLOGS_API FELPrintToScreenLogData
{
	GENERATED_BODY()
public:
	FELPrintToScreenLogData() = default;

	FELPrintToScreenLogData(bool bInPrintToScreen, float InScreenTime, FColor InScreenColor);

public:
	UPROPERTY(EditAnywhere, Category = "Settings")
	bool bPrintToScreen = true;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float ScreenTime = 10.f;

	UPROPERTY(EditAnywhere, Category = "Settings")
	FColor ScreenColor = FColor(127, 127, 127);
};

USTRUCT(BlueprintType)
struct EXTENDEDLOGS_API FELStringFilter
{
	GENERATED_BODY()
public:
	bool IsMatching(const FString& String) const;

public:
	/*
	*A String filter(search by substring) to check for a matching
	*/
	UPROPERTY(EditAnywhere, Category = "Settings")
	FString Filter;

	/*
	 *If true, it replaces string filter(search by substring) to regular expression
	 */
	UPROPERTY(EditAnywhere, Category = "Settings")
	bool bUseFilterAsRegularExpression = false;
};

USTRUCT()
struct EXTENDEDLOGS_API FELLogVerbositySelector
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Settings")
	EELLogVerbosity LogVerbosity = EELLogVerbosity::Log;
};

UCLASS(config = Engine, defaultconfig)
class EXTENDEDLOGS_API UELExtendedLogsSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UELExtendedLogsSettings();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual FText GetSectionText() const override;
	
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSettingsChanged, UObject*, struct FPropertyChangedEvent&);
	FOnSettingsChanged& OnSettingChanged() { return SettingsChangedDelegate; }
	FOnSettingsChanged SettingsChangedDelegate;

#endif //WITH_EDITOR

	static const UELExtendedLogsSettings* Get()
	{
		return GetDefault<UELExtendedLogsSettings>();
	}

public:
	/*
	 * This utility allows you to change the default verbosity of logs
	 * (for declared logs in c++ in the DefaultEngine.ini, for plugins logs in @DeclaredLogCategories)
	 */
	UPROPERTY(EditAnywhere, Category = "Default log verbosity selector")
	FELLogVerbositySelector LogVerbositySelector;

	/*
	 * Declaring log categories without using C ++ (same as DECLARE_LOG_CATEGORY_EXTERN in c++)
	 * You can find more about the declaring logs in the official ue documentation
	 */
	UPROPERTY(EditAnywhere, Config, Category = "Logs")
	TMap<FName, EELLogVerbosity> DeclaredLogCategories;

	/*
	* Allow empty log categories in plugin Log functions
	* (otherwise blueprint with invalid Log function will display warning on compile)
	*/
	UPROPERTY(EditAnywhere, Config, Category = "Logs")
	bool bAllowEmptyLogCategory = true;

	/*
	* Allow categories that were once declared but then removed in plugin Log functions
	* (otherwise blueprint with invalid Log function will display warning on compile)
	*/
	UPROPERTY(EditAnywhere, Config, Category = "Logs")
	bool bAllowInvalidLogCategory = true;

	/*
	* Only log categories matching the filter will be displayed in log category name widget(in details panel or node pin)
	*/
	UPROPERTY(EditAnywhere, Config, Category = "Editor widgets")
	FELStringFilter LogCategoryWidgetFilter;

	/*
	* Default logCategory to initialize plugins Log functions nodes on spawn
	*/
	UPROPERTY(EditAnywhere, Config, Category = "Editor widgets")
	FELLogCategoryName FunctionDefaultLogCategory;

	/*
	* If true, display selected verbosity from @PrintLogsToScreenVerbosityMap to screen
	*/
	UPROPERTY(EditAnywhere, Config, Category = "Screen Logs")
	bool bPrintLogsToScreen = true;

	/*
	* These categories of logs will be displayed to screen
	*/
	UPROPERTY(EditAnywhere, Config, Category = "Screen Logs", meta = (EditCondition = "bPrintLogsToScreen"))
	TMap<EELLogVerbosity, FELPrintToScreenLogData> PrintLogsToScreenVerbosityMap;

	/*
	* Only log categories matching the filter will be displayed on the screen
	*/
	UPROPERTY(EditAnywhere, Config, Category = "Screen Logs")
	FELStringFilter ScreenLogCategoriesFilter;

	UPROPERTY(EditAnywhere, Config, Category = "Screen Logs", AdvancedDisplay)
	bool bClearScreenLogsOnEndPIE = true;
};
