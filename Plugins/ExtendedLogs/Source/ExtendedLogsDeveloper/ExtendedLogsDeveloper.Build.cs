// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class ExtendedLogsDeveloper : ModuleRules
	{
		public ExtendedLogsDeveloper(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
			
			PublicDependencyModuleNames.AddRange(
				new string[] {
					"Core",
					"CoreUObject",
					"Engine",
					"BlueprintGraph",
					
					"ExtendedLogs"
				}
			);
			
			if (Target.bBuildEditor)
			{
				PublicDependencyModuleNames.AddRange(
					new string[] {
						"UnrealEd"
					}
				);
			}
		}
	}
}
 
