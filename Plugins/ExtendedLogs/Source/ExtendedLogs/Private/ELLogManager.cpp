#include "ELLogManager.h"

#include "ELExtendedLogsSettings.h"
#include "ELLogCategory.h"

#include "Algo/AllOf.h"
#include "Logging/LogCategory.h"
#include "Logging/LogSuppressionInterface.h"

/** Log suppression system implementation **/
class FELLogLogSuppressionImplementation : public FLogSuppressionInterface
    , private FSelfRegisteringExec
{
public:
	enum
	{
		NumInlineCategories = 256
	};

	/** Categories waiting to be added to ReverseAssociations */
	TArray<FLogCategoryBase*, TInlineAllocator<NumInlineCategories>> PendingAssociations;

	/** Associates a category name with a set of category pointers  **/
	TMultiMap<FName, FLogCategoryBase*> ReverseAssociations;
	/** Set of verbosity and break values that were set at boot time. **/
	TMap<FName, uint8> BootAssociations;
	/** For a given category stores the last non-zero verbosity...to support toggling without losing the specific verbosity level **/
	TMap<FName, uint8> ToggleAssociations;

	bool bInitialized = false;

	/** Used by FLogCategoryBase to register itself with the global category table **/
	virtual void AssociateSuppress(struct FLogCategoryBase* Destination) override
	{
	}
	/** Used by FLogCategoryBase to unregister itself from the global category table **/
	virtual void DisassociateSuppress(struct FLogCategoryBase* Destination) override
	{
	}
	/** Called by appInit once the config files and commandline are set up. The log suppression system uses these to setup the boot time defaults. **/
	virtual void ProcessConfigAndCommandLine() override
	{
	}
};

void UELLogManager::InitializeManager()
{
	RegisterLogs();
}

TArray<FLogCategoryBase*> UELLogManager::FindLogCategory(FName LogCategoryName) const
{
	TArray<FLogCategoryBase*> foundLogs;
	GetRawLogCategories().MultiFind(LogCategoryName, foundLogs);

	return foundLogs;
}

bool UELLogManager::IsSuppressedLogCategory(FName LogCategoryName, ELogVerbosity::Type Verbosity) const
{
	return Algo::AllOf(FindLogCategory(LogCategoryName), [Verbosity](FLogCategoryBase* LogCategory) {
		return LogCategory != nullptr && LogCategory->IsSuppressed(Verbosity);
	});
}

TArray<FName> UELLogManager::GetLogCategoriesNames() const
{
	TArray<FName> categories;

	for (auto& logData : GetRawLogCategories())
	{
		categories.Add(logData.Key);
	}

	return categories;
}

const TMultiMap<FName, FLogCategoryBase*>& UELLogManager::GetRawLogCategories() const
{
	auto& logInterface = FLogSuppressionInterface::Get();
	FELLogLogSuppressionImplementation& elLogInterface = *reinterpret_cast<FELLogLogSuppressionImplementation*>(&logInterface);

	return elLogInterface.ReverseAssociations;
}

void UELLogManager::RegisterLogs()
{
	auto& settings = UELExtendedLogsSettings::Get();

	for (auto& logCategory : settings.DeclaredLogs)
	{
		DeclaredLogCategories.Add(MakeShareable(new FLogCategoryBase(logCategory.CategoryName, ConvertLogCategory(logCategory.Verbosity), ELogVerbosity::All)));
	}
}