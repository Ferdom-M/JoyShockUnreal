// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using Internal;
using UnrealBuildTool;

public class JoyShockLibrary : ModuleRules
{
	public JoyShockLibrary(ReadOnlyTargetRules target) : base(target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64) // || Target.Platform == UnrealTargetPlatform.Linux || Target.Platform == UnrealTargetPlatform.LinuxAArch64)
		{
			if (Target.Configuration == UnrealTargetConfiguration.Shipping)
			{
				PublicAdditionalLibraries.Add(Path.Combine("$(ModuleDir)", "Release", "JoyShockLibrary.lib"));

				PublicDelayLoadDLLs.Add("JoyShockLibrary.dll");
				RuntimeDependencies.Add("$(ModuleDir)/Release/JoyShockLibrary.dll");
			}
			else
            {
                PublicAdditionalLibraries.Add(Path.Combine("$(ModuleDir)", "Release", "JoyShockLibrary.lib"));

                PublicDelayLoadDLLs.Add("JoyShockLibrary.dll");
                RuntimeDependencies.Add("$(ModuleDir)/Release/JoyShockLibrary.dll");
            }
        }
        else
        {
			//Console.WriteLine("Error: Platform not supported");
        }
    }
}