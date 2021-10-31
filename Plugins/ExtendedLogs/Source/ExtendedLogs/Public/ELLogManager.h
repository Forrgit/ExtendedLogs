#pragma once

#include "UObject/Object.h"

#include "ELLogManager.generated.h"

UCLASS()
class EXTENDEDLOGS_API UELLogManager : public UObject
{
	GENERATED_BODY()
public:
	void InitializeManager();

	TArray<FLogCategoryBase*> FindLogCategory(FName LogCategoryName) const;
	bool IsSuppressedLogCategory(FName LogCategoryName, ELogVerbosity::Type Verbosity) const;

	TArray<FName> GetLogCategoriesNames() const;

#if WITH_EDITOR
	DECLARE_EVENT(UELLogManager, FOnRegisterLogsEvent);
	FOnRegisterLogsEvent OnRegisterLogsEvent;
#endif

protected:
#if WITH_EDITOR
	void OnPluginSettingsChanged(UObject*, struct FPropertyChangedEvent& PropertyChangedEvent);
#endif

	const TMultiMap<FName, FLogCategoryBase*>& GetRawLogCategories() const;
	void RegisterLogs();

private:
	TArray<TSharedPtr<FLogCategoryBase>> DeclaredLogCategories;
};
