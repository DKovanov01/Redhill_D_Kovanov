// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Redhill_D_Kovanov : ModuleRules
{
	public Redhill_D_Kovanov(ReadOnlyTargetRules Target) : base(Target)
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
			"Redhill_D_Kovanov",
			"Redhill_D_Kovanov/Variant_Platforming",
			"Redhill_D_Kovanov/Variant_Platforming/Animation",
			"Redhill_D_Kovanov/Variant_Combat",
			"Redhill_D_Kovanov/Variant_Combat/AI",
			"Redhill_D_Kovanov/Variant_Combat/Animation",
			"Redhill_D_Kovanov/Variant_Combat/Gameplay",
			"Redhill_D_Kovanov/Variant_Combat/Interfaces",
			"Redhill_D_Kovanov/Variant_Combat/UI",
			"Redhill_D_Kovanov/Variant_SideScrolling",
			"Redhill_D_Kovanov/Variant_SideScrolling/AI",
			"Redhill_D_Kovanov/Variant_SideScrolling/Gameplay",
			"Redhill_D_Kovanov/Variant_SideScrolling/Interfaces",
			"Redhill_D_Kovanov/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
