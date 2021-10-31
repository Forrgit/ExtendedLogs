#pragma once

#include "CoreMinimal.h"

class EXTENDEDLOGS_API FELOutputDeviceScreen : public FOutputDevice
{
public:
	FELOutputDeviceScreen();
	virtual ~FELOutputDeviceScreen() override;

	virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category) override;
};
