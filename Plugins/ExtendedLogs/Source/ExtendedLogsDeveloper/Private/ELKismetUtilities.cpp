#include "ELKismetUtilities.h"

#include "EdGraph/EdGraphPin.h"
#include "Misc/OutputDeviceError.h"

namespace ELKismetUtilities
{
bool GetLogCategoryNamePinDefaultValue(UEdGraphPin* Pin, FELLogCategoryName& OutValue)
{
	const auto pinDefaultValue = Pin->GetDefaultAsString();

	if (!pinDefaultValue.IsEmpty())
	{
		auto logCategoryStructType = FELLogCategoryName::StaticStruct();

		const auto buffer = logCategoryStructType->ImportText(*pinDefaultValue, &OutValue, nullptr, EPropertyPortFlags::PPF_SerializedAsImportText, GError, logCategoryStructType->GetName(), true);

		return buffer != nullptr;
	}
	return false;
}
} // namespace ELKismetUtilities