// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Asst2_EODriscoll : ModuleRules
{
	public Asst2_EODriscoll(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "NavigationSystem", "AIModule" });
	}
}
