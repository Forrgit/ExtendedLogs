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

protected:
	const TMultiMap<FName, FLogCategoryBase*>& GetRawLogCategories() const;

	void RegisterLogs();

private:
	TArray<TSharedPtr<FLogCategoryBase>> DeclaredLogCategories;
};
