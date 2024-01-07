// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h" 
#include <Windows/WindowsApplication.h>
#include <JoyShockUnreal.h>

class FJoyShockUnrealWindows : public FJoyShockUnreal, IWindowsMessageHandler
{
public:
	FJoyShockUnrealWindows(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);

	virtual ~FJoyShockUnrealWindows() {}

	virtual bool ProcessMessage(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam, int32& OutResult) override;
};