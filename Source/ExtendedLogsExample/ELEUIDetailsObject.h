#pragma once

#include "CoreMinimal.h"

#include "ELEUIDetailsObject.generated.h"

class UELExtendedLogsSettings;

UCLASS(BlueprintType)
class UELEUIDetailsObject : public UObject
{
	GENERATED_BODY()
public:
	UELEUIDetailsObject();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UELExtendedLogsSettings* Settings;
};