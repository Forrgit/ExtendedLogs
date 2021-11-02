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
	UPROPERTY(EditAnywhere)
	bool bPrintToScreen = true;

	UPROPERTY(EditAnywhere)
	float ScreenTime = 10.f;

	UPROPERTY(EditAnywhere)
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
	UPROPERTY(EditAnywhere)
	FString Filter;

	/*
	 *If true, it replaces string filter(search by substring) to regular expression
	 */
	UPROPERTY(EditAnywhere)
	bool bUseFilterAsRegularExpression = false;
};

USTRUCT()
struct EXTENDEDLOGS_API FELLogVerbositySelector
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
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
#endif //WITH_EDITOR

	static const UELExtendedLogsSettings* Get()
	{
		return GetDefault<UELExtendedLogsSettings>();
	}

public:
	UPROPERTY(EditAnywhere, Category = "Default log verbosity selector")
	FELLogVerbositySelector LogVerbositySelector;

	UPROPERTY(EditAnywhere, Config, Category = "Logs")
	FELLogCategoryName FunctionDefaultLogCategory;

	UPROPERTY(EditAnywhere, Config, Category = "Logs")
	TMap<FName, EELLogVerbosity> DeclaredLogCategories;

	UPROPERTY(EditAnywhere, Config, Category = "Logs")
	bool bAllowEmptyLogCategory = true;

	UPROPERTY(EditAnywhere, Config, Category = "Logs")
	bool bAllowInvalidLogCategory = true;

	/*
	* Only log categories matching the filter will be displayed in log category name widget(in details panel or node pin)
	*/
	UPROPERTY(EditAnywhere, Config, Category = "Editor widgets")
	FELStringFilter LogCategoryWidgetFilter;

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
