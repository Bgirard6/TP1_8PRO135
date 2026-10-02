// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TP1_8PRO135 : ModuleRules
{
	public TP1_8PRO135(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"TP1_8PRO135",
			"TP1_8PRO135/Variant_Platforming",
			"TP1_8PRO135/Variant_Platforming/Animation",
			"TP1_8PRO135/Variant_Combat",
			"TP1_8PRO135/Variant_Combat/AI",
			"TP1_8PRO135/Variant_Combat/Animation",
			"TP1_8PRO135/Variant_Combat/Gameplay",
			"TP1_8PRO135/Variant_Combat/Interfaces",
			"TP1_8PRO135/Variant_Combat/UI",
			"TP1_8PRO135/Variant_SideScrolling",
			"TP1_8PRO135/Variant_SideScrolling/AI",
			"TP1_8PRO135/Variant_SideScrolling/Gameplay",
			"TP1_8PRO135/Variant_SideScrolling/Interfaces",
			"TP1_8PRO135/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
