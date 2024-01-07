// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Windows/JoyShockUnrealWindows.h"

FJoyShockUnrealWindows::FJoyShockUnrealWindows(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
	: FJoyShockUnreal(InMessageHandler)
{
	FWindowsApplication* WindowsApplication = (FWindowsApplication*)FSlateApplication::Get().GetPlatformApplication().Get();
	check(WindowsApplication);

	WindowsApplication->AddMessageHandler(*this);
};

bool FJoyShockUnrealWindows::ProcessMessage(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam, int32& OutResult)
{
	bool bHandled = false;
	if (msg == WM_DEVICECHANGE)
	{
		QueryConnectedDevices();
		bHandled = true;
	}
	return bHandled;
}