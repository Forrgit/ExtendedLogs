
#include "ELEUIDetailsObject.h"

#include "ELExtendedLogsSettings.h"

UELEUIDetailsObject::UELEUIDetailsObject()
{
	Settings = GetMutableDefault<UELExtendedLogsSettings>();
}
