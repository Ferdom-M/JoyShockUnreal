// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "JoyShockUnrealFunctionLibrary.h"
#include "JoyShockDeviceInfo.h"

TArray<FJoyShockDeviceInfo> UJoyShockFunctionLibrary::GetRegisteredDevices()
{
	TArray<FJoyShockDeviceInfo> JoyShockDevices;
	FJoyShockUnreal* JoyShock = static_cast<FJoyShockUnreal*>(static_cast<FJoyShockUnrealPlugin*>(&FJoyShockUnrealPlugin::Get())->GetJoyShockDevice().Get());

	if (!JoyShock) return JoyShockDevices;

	const TArray<FJoyShockDeviceEntry>& Devices = JoyShock->GetDevices();
	JoyShockDevices.Reserve(Devices.Num());
	for (int i = 0; i < Devices.Num(); ++i)
	{
		FJoyShockDeviceInfo DeviceInfo;
		DeviceInfo.bIsJoyconPair = Devices[i].bIsJoyconPair;
		DeviceInfo.DeviceId = Devices[i].DeviceId;
		DeviceInfo.DeviceType = Devices[i].DeviceType;
		DeviceInfo.DeviceId2 = Devices[i].DeviceId2;
		DeviceInfo.DeviceType2 = Devices[i].DeviceType2;
		DeviceInfo.PlayerId = Devices[i].PlayerId;
		JoyShockDevices.Add(DeviceInfo);
	}

	return JoyShockDevices;
}

FJoyShockControllerColor UJoyShockFunctionLibrary::GetControllerColorsByControllerId(int _ControllerId)
{
	FJoyShockUnreal* JoyShock = FJoyShockUnrealPlugin::Get().GetJoyShockDevice().Get();

	FJoyShockControllerColor ControllerColor;
	if (!JoyShock) return ControllerColor;
	TPair<int, int> DeviceId = JoyShock->GetDeviceIdByPlayerId(_ControllerId);

	int BodyColor = 0xFFFFFF, LeftButtonColor = 0xFFFFFF, RightButtonColor = 0xFFFFFF, LeftGripColor = 0xFFFFFF, RightGripColor = 0xFFFFFF;
	if(JslGetControllerType(DeviceId.Key) == JS_TYPE_JOYCON_LEFT)
	{
		LeftGripColor = JslGetControllerBodyColour(DeviceId.Key);
		LeftButtonColor = JslGetControllerButtonColour(DeviceId.Key);
		RightGripColor = JslGetControllerBodyColour(DeviceId.Value);
		RightButtonColor = JslGetControllerButtonColour(DeviceId.Value);
	}
	else if (JslGetControllerType(DeviceId.Key) == JS_TYPE_JOYCON_RIGHT)
	{
		LeftGripColor = JslGetControllerBodyColour(DeviceId.Value);
		LeftButtonColor = JslGetControllerButtonColour(DeviceId.Value);
		RightGripColor = JslGetControllerBodyColour(DeviceId.Key);
		RightButtonColor = JslGetControllerButtonColour(DeviceId.Key);
	}
	else
	{
		BodyColor = JslGetControllerBodyColour(DeviceId.Key);
		LeftButtonColor = JslGetControllerButtonColour(DeviceId.Key);
		RightButtonColor = LeftButtonColor;
		LeftGripColor = JslGetControllerLeftGripColour(DeviceId.Key);
		RightGripColor = JslGetControllerRightGripColour(DeviceId.Key);
	}

	return IntToControllerColor(BodyColor, LeftButtonColor, RightButtonColor, LeftGripColor, RightGripColor);
}


FJoyShockControllerColor UJoyShockFunctionLibrary::GetControllerColorsByDeviceId(int _DeviceId)
{
	int BodyColor = 0xFFFFFF, LeftButtonColor = 0xFFFFFF, RightButtonColor = 0xFFFFFF, LeftGripColor = 0xFFFFFF, RightGripColor = 0xFFFFFF;
	if (JslGetControllerType(_DeviceId) == JS_TYPE_JOYCON_LEFT)
	{
		LeftGripColor = JslGetControllerBodyColour(_DeviceId);
	}
	else if (JslGetControllerType(_DeviceId) == JS_TYPE_JOYCON_RIGHT)
	{
		RightGripColor = JslGetControllerBodyColour(_DeviceId);
	}
	else
	{
		BodyColor = JslGetControllerBodyColour(_DeviceId);
		LeftButtonColor = JslGetControllerButtonColour(_DeviceId);
		RightButtonColor = LeftButtonColor;
		LeftGripColor = JslGetControllerLeftGripColour(_DeviceId);
		RightGripColor = JslGetControllerRightGripColour(_DeviceId);
	}

	return IntToControllerColor(BodyColor, LeftButtonColor, RightButtonColor, LeftGripColor, RightGripColor);
}


void UJoyShockFunctionLibrary::SetControllerLightColorByDeviceId(int _DeviceId, const FColor& _Color)
{
	int LightColor;
	LightColor = (_Color.R << 16) & 0x00ff0000;
	LightColor += (_Color.G << 8) & 0x0000ff00;
	LightColor += (_Color.B) & 0x000000ff;

	JslSetLightColour(_DeviceId, LightColor);
}

void UJoyShockFunctionLibrary::SetControllerLightColorByControllerId(int _ControllerId, const FColor& _Color)
{
	FJoyShockUnreal* JoyShock = FJoyShockUnrealPlugin::Get().GetJoyShockDevice().Get();

	if (!JoyShock) return;

	TPair<int, int> DeviceId = JoyShock->GetDeviceIdByPlayerId(_ControllerId);
	SetControllerLightColorByDeviceId(DeviceId.Key, _Color);
}


bool UJoyShockFunctionLibrary::JoinJoyconsByDeviceId(int _DeviceId, int _DeviceId2)
{
	FJoyShockUnreal* JoyShock = FJoyShockUnrealPlugin::Get().GetJoyShockDevice().Get();

	if (!JoyShock) return false;

	return JoyShock->JoinJoyconsByDeviceId(_DeviceId, _DeviceId2);
}


bool UJoyShockFunctionLibrary::JoinJoyconsByControllerId(int _ControllerId, int _ControllerId2)
{
	FJoyShockUnreal* JoyShock = FJoyShockUnrealPlugin::Get().GetJoyShockDevice().Get();

	if (!JoyShock) return false;

	return JoyShock->JoinJoyconsByControllerId(_ControllerId, _ControllerId2);
}


bool UJoyShockFunctionLibrary::QueryConnectedDevices()
{
	FJoyShockUnreal* JoyShock = FJoyShockUnrealPlugin::Get().GetJoyShockDevice().Get();

	if (!JoyShock) return false;

	JoyShock->QueryConnectedDevices();
	return true;
}


bool UJoyShockFunctionLibrary::DisconnectAllDevices()
{
	FJoyShockUnreal* JoyShock = FJoyShockUnrealPlugin::Get().GetJoyShockDevice().Get();

	if (!JoyShock) return false;

	JoyShock->DisconnectAllDevices();
	return true;
}

void UJoyShockFunctionLibrary::GetDeviceIdByPlayerId(int _PlayerId, int& DeviceId_, int& DeviceId2_)
{
	FJoyShockUnreal* JoyShock = FJoyShockUnrealPlugin::Get().GetJoyShockDevice().Get();
	
	DeviceId_ = -1;
	DeviceId2_ = -1;

	if (!JoyShock) return;

	TPair<int, int> DeviceIds = JoyShock->GetDeviceIdByPlayerId(_PlayerId);
	
	DeviceId_ = DeviceIds.Key;
	DeviceId2_ = DeviceIds.Value;
}

bool UJoyShockFunctionLibrary::SetPlayerIdByDeviceId(int _DeviceId, int _PlayerId)
{
	FJoyShockUnreal* JoyShock = FJoyShockUnrealPlugin::Get().GetJoyShockDevice().Get();

	if (!JoyShock) return false;

	JoyShock->SetPlayerIdByDeviceId(_DeviceId, _PlayerId); 
	return true;
}


int UJoyShockFunctionLibrary::GetNumJoyShockDevices()
{
	FJoyShockUnreal* JoyShock = FJoyShockUnrealPlugin::Get().GetJoyShockDevice().Get();

	if (!JoyShock) return -1;

	return JoyShock->GetNumJoyShockDevices();
}


int UJoyShockFunctionLibrary::GetNumJoyShockPlayers()
{
	FJoyShockUnreal* JoyShock = FJoyShockUnrealPlugin::Get().GetJoyShockDevice().Get();

	if (!JoyShock) return -1;

	return JoyShock->GetNumJoyShockPlayers();
}

FOnJoyShockDeviceConnected* UJoyShockFunctionLibrary::GetOnDeviceConnectedDelegate()
{
	FJoyShockUnreal* JoyShock = FJoyShockUnrealPlugin::Get().GetJoyShockDevice().Get();

	if (!JoyShock) return nullptr;
	return &JoyShock->OnJoyShockDeviceConnected;
}

FOnJoyShockDeviceDisconnected* UJoyShockFunctionLibrary::GetOnDeviceDisconnectedDelegate()
{
	FJoyShockUnreal* JoyShock = FJoyShockUnrealPlugin::Get().GetJoyShockDevice().Get();

	if (!JoyShock) return nullptr;
	return &JoyShock->OnJoyShockDeviceDisconnected;
}

FJoyShockControllerColor UJoyShockFunctionLibrary::IntToControllerColor(int _BodyColor, int _LeftButtonColor, int _RightButtonColor, int _LeftGripColor, int _RightGripColor)
{
	FJoyShockControllerColor ControllerColor;

	ControllerColor.BodyColor.R = (_BodyColor >> 16) & 0xFF;
	ControllerColor.BodyColor.G = (_BodyColor >> 8) & 0xFF;
	ControllerColor.BodyColor.B = _BodyColor & 0xFF;
	ControllerColor.BodyColor.A = 255;

	ControllerColor.LeftButtonColor.R = (_LeftButtonColor >> 16) & 0xFF;
	ControllerColor.LeftButtonColor.G = (_LeftButtonColor >> 8) & 0xFF;
	ControllerColor.LeftButtonColor.B = _LeftButtonColor & 0xFF;
	ControllerColor.LeftButtonColor.A = 255;

	ControllerColor.RightButtonColor.R = (_RightButtonColor >> 16) & 0xFF;
	ControllerColor.RightButtonColor.G = (_RightButtonColor >> 8) & 0xFF;
	ControllerColor.RightButtonColor.B = _RightButtonColor & 0xFF;
	ControllerColor.RightButtonColor.A = 255;

	ControllerColor.LeftGripColor.R = (_LeftGripColor >> 16) & 0xFF;
	ControllerColor.LeftGripColor.G = (_LeftGripColor >> 8) & 0xFF;
	ControllerColor.LeftGripColor.B = _LeftGripColor & 0xFF;
	ControllerColor.LeftGripColor.A = 255;

	ControllerColor.RightGripColor.R = (_RightGripColor >> 16) & 0xFF;
	ControllerColor.RightGripColor.G = (_RightGripColor >> 8) & 0xFF;
	ControllerColor.RightGripColor.B = _RightGripColor & 0xFF;
	ControllerColor.RightGripColor.A = 255;

	return ControllerColor;
}