// Copyright 2021 Alexander Shumeyko. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class ExtendedLogsEditor : ModuleRules
	{
		public ExtendedLogsEditor(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
			
			PublicDependencyModuleNames.AddRange(
				new string[] {
					"Core",
					"CoreUObject",
					"Engine",
					"SlateCore",
					"Slate",
					"InputCore",
					"GraphEditor",
					"BlueprintGraph",
					"UnrealEd",
					"EditorWidgets",
					"PropertyEditor",
					"DeveloperSettings",
					
					"ExtendedLogsDeveloper",
					"ExtendedLogs"
				}
			);
		}
	}
}
 
