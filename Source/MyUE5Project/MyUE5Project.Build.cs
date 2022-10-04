// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyUE5Project : ModuleRules
{
	public MyUE5Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
