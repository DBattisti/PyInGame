// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class PythonLibrary : ModuleRules
{
	public PythonLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, "x64", "Release"));
			PublicAdditionalLibraries.Add("python36.lib");
            
            // Add the includes paths of python
            PublicSystemIncludePaths.Add(Path.Combine(ModuleDirectory, "x64", "Includes"));

            // Delay-load the DLL, so we can load it from the right place first
            PublicDelayLoadDLLs.Add("python36.dll");
		}
	}
}
