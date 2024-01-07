// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using System;

namespace UnrealBuildTool.Rules
{
	public class JoyShockUnreal : ModuleRules
	{
		public JoyShockUnreal(ReadOnlyTargetRules Target) : base(Target)
		{
            PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

            PublicIncludePaths.AddRange(
                new[] 
				{
					PluginDirectory + "/Source/ThirdParty/JoyShockLibrary"
                }
            );

            PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
				    "CoreUObject",
				    "Engine",
					"JoyShockLibrary",
					"Projects",
                    "InputCore",
					"SlateCore",
					"Slate"
				}
			);

            PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"InputDevice",
                    "DeveloperSettings",
				}
			);
		}
	}
}
