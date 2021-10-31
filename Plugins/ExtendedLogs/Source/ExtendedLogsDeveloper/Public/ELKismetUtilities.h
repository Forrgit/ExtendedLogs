#pragma once

#include "ELTypes.h"

class UEdGraphPin;

namespace ELKismetUtilities
{
bool GetLogCategoryNamePinDefaultValue(UEdGraphPin* Pin, FELLogCategoryName& OutValue);
}
