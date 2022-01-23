// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectGwen : ModuleRules
{
	public ProjectGwen(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
			"HeadMountedDisplay", "GameplayAbilities", "PaulsUtilities" });
	}
}
