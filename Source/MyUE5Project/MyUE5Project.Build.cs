// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyUE5Project : ModuleRules
{
	public MyUE5Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		// Add "AkAudio" to use and compile Wwise's API in C++
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
			"HeadMountedDisplay", "AkAudio" });
	}
}
