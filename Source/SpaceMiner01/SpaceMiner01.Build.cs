// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SpaceMiner01 : ModuleRules
{
	public SpaceMiner01(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
		"Core", 
		"CoreUObject", 
		"Engine", 
		"InputCore", 
		"EnhancedInput",
		// Mass Modules
            "MassEntity",
            "MassCommon",
            "MassGameplay",
            "MassSignals",
            "MassRepresentation",
            "StructUtils" // Required for many Mass data structures		
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
