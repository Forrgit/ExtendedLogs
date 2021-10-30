#pragma once

#include "CoreMinimal.h"

class EXTENDEDLOGS_API FELOutputDeviceScreen : public FOutputDevice
{
public:
	virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category) override;
};
