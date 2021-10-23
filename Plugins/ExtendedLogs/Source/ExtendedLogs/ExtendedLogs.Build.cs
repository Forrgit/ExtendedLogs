// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class ExtendedLogs : ModuleRules
	{
		public ExtendedLogs(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

			PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"Engine"
			}
			);
		}
	}
}
 
