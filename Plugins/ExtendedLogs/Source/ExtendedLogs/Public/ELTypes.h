// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

#include "ELTypes.generated.h"

USTRUCT(BlueprintType)
struct EXTENDEDLOGS_API FELLogCategoryName
{
	GENERATED_BODY()
public:
	FELLogCategoryName() = default;
	FELLogCategoryName(FName InName)
	    : Name(InName)
	{
	}

	bool IsValid() const
	{
		return Name != NAME_None;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
};

UENUM(BlueprintType)
enum class EELLogVerbosity : uint8
{
	/** Not used */
	NoLogging = 0,

	/** Always prints a fatal error to console (and log file) and crashes (even if,
	* logging is disabled) */
	Fatal,

	/**
	* Prints an error to console (and log file).
	* Commandlets and the editor collect and report errors. Error messages result
	* in commandlet failure.
	*/
	Error,

	/**
	* Prints a warning to console (and log file).
	* Commandlets and the editor collect and report warnings. Warnings can be
	* treated as an error.
	*/
	Warning,

	/** Prints a message to console (and log file) */
	Display,

	/** Prints a message to a log file (does not print to console) */
	Log,

	/**
	* Prints a verbose message to a log file (if Verbose logging is enabled for
	* the given category, usually used for detailed logging)
	*/
	Verbose,

	/**
	*
	* Prints a verbose message to a log file (if VeryVerbose logging is enabled,
	* usually used for detailed logging that would otherwise spam output)
	*/
	VeryVerbose,
};

static_assert(static_cast<uint8>(EELLogVerbosity::NoLogging) == static_cast<uint8>(ELogVerbosity::NoLogging), "EELogVerbosity start log category must be equals with ELogVerbosity");

static_assert(static_cast<uint8>(EELLogVerbosity::VeryVerbose) == static_cast<uint8>(ELogVerbosity::VeryVerbose), "EELogVerbosity end log category must be equals with ELogVerbosity");

inline EXTENDEDLOGS_API ELogVerbosity::Type ConvertLogVerbosity(EELLogVerbosity LogVerbosity)
{
	return static_cast<ELogVerbosity::Type>(LogVerbosity);
}

inline EXTENDEDLOGS_API EELLogVerbosity ConvertLogVerbosity(ELogVerbosity::Type LogVerbosity)
{
	return static_cast<EELLogVerbosity>(LogVerbosity);
}

inline EXTENDEDLOGS_API FString GetVerbosityString(EELLogVerbosity Verbosity)
{
	UEnum* enumClass = StaticEnum<EELLogVerbosity>();
	check(enumClass != nullptr);
	check(enumClass->GetCppForm() == UEnum::ECppForm::EnumClass);

	FString enumValueString = enumClass->GetNameStringByValue(static_cast<int32>(Verbosity));
	enumValueString.RemoveFromStart(enumClass->CppType + TEXT("::"));
	return enumValueString;
}