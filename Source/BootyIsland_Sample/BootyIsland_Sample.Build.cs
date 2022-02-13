// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BootyIsland_Sample : ModuleRules
{
	public BootyIsland_Sample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
