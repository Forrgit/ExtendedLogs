// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "ELTypes.h"

class UEdGraphPin;

namespace ELKismetUtilities
{
bool EXTENDEDLOGSDEVELOPER_API GetLogCategoryNamePinDefaultValue(UEdGraphPin* Pin, FELLogCategoryName& OutValue);

bool EXTENDEDLOGSDEVELOPER_API SetLogCategoryNamePinDefaultValue(UEdGraphPin* Pin, const FELLogCategoryName& Value);

} // namespace ELKismetUtilities
