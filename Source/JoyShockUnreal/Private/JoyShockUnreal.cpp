// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "JoyShockUnreal.h"
#include "Misc/MessageDialog.h"
#include "Modules/ModuleManager.h"
#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"
#include "IInputDeviceModule.h"
#include "IInputDevice.h"
#include "Interfaces/IPluginManager.h"
#include <Misc/MessageDialog.h>
#include <JoyShockUnrealFunctionLibrary.h>
#include <JoyShockLibrary.h>

#if PLATFORM_WINDOWS
#include "Windows/JoyShockUnrealWindows.h"
#endif

#define LOCTEXT_NAMESPACE "JoyShockUnrealPlugin"

const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_LeftX("Gamepad_LeftX");
const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_LeftY("Gamepad_LeftY");
const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_RightX("Gamepad_RightX");
const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_RightY("Gamepad_RightY");
const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_LeftTriggerAxis("Gamepad_LeftTriggerAxis");
const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_RightTriggerAxis("Gamepad_RightTriggerAxis");

const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_DPad_Up("Gamepad_DPad_Up");
const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_DPad_Down("Gamepad_DPad_Down");
const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_DPad_Right("Gamepad_DPad_Right");
const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_DPad_Left("Gamepad_DPad_Left");
const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_Special_Right("Gamepad_Special_Right");
const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_Special_Left("Gamepad_Special_Left");
const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_LeftThumbstick("Gamepad_LeftThumbstick");
const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_RightThumbstick("Gamepad_RightThumbstick");
const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_LeftShoulder("Gamepad_LeftShoulder");
const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_RightShoulder("Gamepad_RightShoulder");
const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_LeftTrigger("Gamepad_LeftTrigger");
const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_RightTrigger("Gamepad_RightTrigger");
const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_FaceButton_Bottom("Gamepad_FaceButton_Bottom");
const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_FaceButton_Left("Gamepad_FaceButton_Left");
const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_FaceButton_Right("Gamepad_FaceButton_Right");
const FGamepadKeyNames::Type FJoyShockKeyNames::Gamepad_FaceButton_Top("Gamepad_FaceButton_Top");

const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_SwitchCapture("JoyShock_SwitchCapture");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_Home("JoyShock_Home");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_TouchpadPress("JoyShock_TouchpadPress");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_LeftJoyconSL("JoyShock_LeftJoyconSL");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_LeftJoyconSR("JoyShock_LeftJoyconSR");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_RightJoyconSL("JoyShock_RightJoyconSL");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_RightJoyconSR("JoyShock_RightJoyconSR");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_JoyconSL( "JoyShock_JoyconSL" );
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_JoyconSR( "JoyShock_JoyconSR" );
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_DualsenseCreate( "JoyShock_DualsenseCreate" );
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_DualsenseMic( "JoyShock_DualsenseMic" );

const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_FirstPressTouchpad( "JoyShock_FirstPressTouchpad" );
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_FirstPressTouchpadX( "JoyShock_FirstPressTouchpadX" );
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_FirstPressTouchpadY("JoyShock_FirstPressTouchpadY");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_FirstPressTouchpad2D("JoyShock_FirstPressTouchpad2D");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_SecondPressTouchpad("JoyShock_SecondPressTouchpad");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_SecondPressTouchpadX("JoyShock_SecondPressTouchpadX");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_SecondPressTouchpadY("JoyShock_SecondPressTouchpadY");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_SecondPressTouchpad2D("JoyShock_SecondPressTouchpad2D");

const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_LeftJoyconAccelX("JoyShock_LeftJoyconAccelX");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_LeftJoyconAccelY("JoyShock_LeftJoyconAccelY");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_LeftJoyconAccelZ("JoyShock_LeftJoyconAccelZ");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_LeftJoyconAccel3D("JoyShock_LeftJoyconAccel3D");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_LeftJoyconGyroX("JoyShock_LeftJoyconGyroX");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_LeftJoyconGyroY("JoyShock_LeftJoyconGyroY");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_LeftJoyconGyroZ("JoyShock_LeftJoyconGyroZ");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_LeftJoyconGyro3D("JoyShock_LeftJoyconGyro3D");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_LeftJoyconOrientationX("JoyShock_LeftJoyconOrientationX");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_LeftJoyconOrientationY("JoyShock_LeftJoyconOrientationY");
const FGamepadKeyNames::Type FJoyShockKeyNames::JoyShock_LeftJoyconOrientationZ("JoyShock_LeftJoyconOrientationZ");


const FKey FJoyShockKeys::JoyShock_SwitchCapture(FJoyShockKeyNames::JoyShock_SwitchCapture);
const FKey FJoyShockKeys::JoyShock_Home(FJoyShockKeyNames::JoyShock_Home);
const FKey FJoyShockKeys::JoyShock_TouchpadPress(FJoyShockKeyNames::JoyShock_TouchpadPress);
const FKey FJoyShockKeys::JoyShock_LeftJoyconSL(FJoyShockKeyNames::JoyShock_LeftJoyconSL);
const FKey FJoyShockKeys::JoyShock_LeftJoyconSR(FJoyShockKeyNames::JoyShock_LeftJoyconSR);
const FKey FJoyShockKeys::JoyShock_RightJoyconSL(FJoyShockKeyNames::JoyShock_RightJoyconSL);
const FKey FJoyShockKeys::JoyShock_RightJoyconSR(FJoyShockKeyNames::JoyShock_RightJoyconSR);
const FKey FJoyShockKeys::JoyShock_JoyconSL(FJoyShockKeyNames::JoyShock_JoyconSL);
const FKey FJoyShockKeys::JoyShock_JoyconSR(FJoyShockKeyNames::JoyShock_JoyconSR);
const FKey FJoyShockKeys::JoyShock_DualsenseCreate(FJoyShockKeyNames::JoyShock_DualsenseCreate);
const FKey FJoyShockKeys::JoyShock_DualsenseMic(FJoyShockKeyNames::JoyShock_DualsenseMic);

const FKey FJoyShockKeys::JoyShock_FirstPressTouchpad(FJoyShockKeyNames::JoyShock_FirstPressTouchpad);
const FKey FJoyShockKeys::JoyShock_FirstPressTouchpadX(FJoyShockKeyNames::JoyShock_FirstPressTouchpadX);
const FKey FJoyShockKeys::JoyShock_FirstPressTouchpadY(FJoyShockKeyNames::JoyShock_FirstPressTouchpadY);
const FKey FJoyShockKeys::JoyShock_FirstPressTouchpad2D(FJoyShockKeyNames::JoyShock_FirstPressTouchpad2D);
const FKey FJoyShockKeys::JoyShock_SecondPressTouchpad(FJoyShockKeyNames::JoyShock_SecondPressTouchpad);
const FKey FJoyShockKeys::JoyShock_SecondPressTouchpadX(FJoyShockKeyNames::JoyShock_SecondPressTouchpadX);
const FKey FJoyShockKeys::JoyShock_SecondPressTouchpadY(FJoyShockKeyNames::JoyShock_SecondPressTouchpadY);
const FKey FJoyShockKeys::JoyShock_SecondPressTouchpad2D(FJoyShockKeyNames::JoyShock_SecondPressTouchpad2D);

const FKey FJoyShockKeys::JoyShock_LeftJoyconAccelX(FJoyShockKeyNames::JoyShock_LeftJoyconAccelX);
const FKey FJoyShockKeys::JoyShock_LeftJoyconAccelY(FJoyShockKeyNames::JoyShock_LeftJoyconAccelY);
const FKey FJoyShockKeys::JoyShock_LeftJoyconAccelZ(FJoyShockKeyNames::JoyShock_LeftJoyconAccelZ);
const FKey FJoyShockKeys::JoyShock_LeftJoyconAccel3D(FJoyShockKeyNames::JoyShock_LeftJoyconAccel3D);
const FKey FJoyShockKeys::JoyShock_LeftJoyconGyroX(FJoyShockKeyNames::JoyShock_LeftJoyconGyroX);
const FKey FJoyShockKeys::JoyShock_LeftJoyconGyroY(FJoyShockKeyNames::JoyShock_LeftJoyconGyroY);
const FKey FJoyShockKeys::JoyShock_LeftJoyconGyroZ(FJoyShockKeyNames::JoyShock_LeftJoyconGyroZ);
const FKey FJoyShockKeys::JoyShock_LeftJoyconGyro3D(FJoyShockKeyNames::JoyShock_LeftJoyconGyro3D);
const FKey FJoyShockKeys::JoyShock_LeftJoyconOrientationX(FJoyShockKeyNames::JoyShock_LeftJoyconOrientationX);
const FKey FJoyShockKeys::JoyShock_LeftJoyconOrientationY(FJoyShockKeyNames::JoyShock_LeftJoyconOrientationY);
const FKey FJoyShockKeys::JoyShock_LeftJoyconOrientationZ(FJoyShockKeyNames::JoyShock_LeftJoyconOrientationZ);

FJoyShockUnreal::FJoyShockUnreal(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
	: MessageHandler(InMessageHandler)
	, LastAssignedInputHandle(0)
{
	ButtonMap.Add(0x00001, FJoyShockKeyNames::Gamepad_DPad_Up);
	ButtonMap.Add(0x00002, FJoyShockKeyNames::Gamepad_DPad_Down);
	ButtonMap.Add(0x00004, FJoyShockKeyNames::Gamepad_DPad_Left);
	ButtonMap.Add(0x00008, FJoyShockKeyNames::Gamepad_DPad_Right);
	ButtonMap.Add(0x00010, FJoyShockKeyNames::Gamepad_Special_Right);
	ButtonMap.Add(0x00020, FJoyShockKeyNames::Gamepad_Special_Left);
	ButtonMap.Add(0x00040, FJoyShockKeyNames::Gamepad_LeftThumbstick);
	ButtonMap.Add(0x00080, FJoyShockKeyNames::Gamepad_RightThumbstick);
	ButtonMap.Add(0x00100, FJoyShockKeyNames::Gamepad_LeftShoulder);
	ButtonMap.Add(0x00200, FJoyShockKeyNames::Gamepad_RightShoulder);
	ButtonMap.Add(0x00400, FJoyShockKeyNames::Gamepad_LeftTrigger);
	ButtonMap.Add(0x00800, FJoyShockKeyNames::Gamepad_RightTrigger);
	ButtonMap.Add(0x01000, FJoyShockKeyNames::Gamepad_FaceButton_Bottom);
	ButtonMap.Add(0x02000, FJoyShockKeyNames::Gamepad_FaceButton_Right);
	ButtonMap.Add(0x04000, FJoyShockKeyNames::Gamepad_FaceButton_Left);
	ButtonMap.Add(0x08000, FJoyShockKeyNames::Gamepad_FaceButton_Top);
	ButtonMap.Add(0x10000, FJoyShockKeyNames::JoyShock_Home);

	QueryConnectedDevices();
};


void FJoyShockUnreal::QueryConnectedDevices()
{
	int OldConnectedDevices = ConnectedDevices;
	ConnectedDevices = JslConnectDevices();

	if (ConnectedDevices != OldConnectedDevices)
	{
		if (ConnectedDevices == 0)
		{
			Devices.Empty();
			ConnectedDeviceIds.Empty();
			return;
		}

		TArray<int> DeviceIds;
		DeviceIds.AddUninitialized(ConnectedDevices);
		JslGetConnectedDeviceHandles(DeviceIds.GetData(), DeviceIds.Num());

		for (int i = 0; i < DeviceIds.Num(); ++i)
		{
			RegisterInputDevice(i, DeviceIds[i], JslGetControllerType(DeviceIds[i]));
			JslSetAutomaticCalibration(DeviceIds[i], true);
		}
		TSet<int> DevicesToRemove;
		for (int DeviceId : ConnectedDeviceIds)
		{
			if (!DeviceIds.ContainsByPredicate([DeviceId](const int NewDeviceId) { return DeviceId == NewDeviceId; }))
			{
				DevicesToRemove.Add(DeviceId);
			}
		}
		for (int DeviceId : DevicesToRemove)
		{
			RemoveRegisteredInputDeviceByDeviceId(DeviceId);
		}
		JoinJoyconsByDeviceId(0, 1);
	}
}


void FJoyShockUnreal::DisconnectAllDevices()
{
	JslDisconnectAndDisposeAll();

	Devices.Empty();
	ConnectedDeviceIds.Empty();
	ConnectedDevices = 0;
}

void FJoyShockUnreal::RegisterInputDevice(int _PlayerId, int _DeviceId, int _DeviceType, int _IndexToJoinJoycon /* = -1 */)
{

	if(Devices.IsValidIndex(_IndexToJoinJoycon))
	{
		int IndexToRemove = GetIndexByDeviceId(_DeviceId);
		Devices[_IndexToJoinJoycon].DeviceId2 = _DeviceId;
		Devices[_IndexToJoinJoycon].DeviceType2 = _DeviceType;
		Devices[_IndexToJoinJoycon].bIsJoyconPair = true; 
		RemoveRegisteredInputDeviceByIndex(IndexToRemove);

		FJoyShockDeviceInfo DeviceInfo;
		DeviceInfo.PlayerId = Devices[_IndexToJoinJoycon].PlayerId;
		DeviceInfo.bIsJoyconPair = Devices[_IndexToJoinJoycon].bIsJoyconPair;
		DeviceInfo.DeviceId = Devices[_IndexToJoinJoycon].DeviceId;
		DeviceInfo.DeviceType = Devices[_IndexToJoinJoycon].DeviceType;
		DeviceInfo.DeviceId2 = Devices[_IndexToJoinJoycon].DeviceId2;
		DeviceInfo.DeviceType2 = Devices[_IndexToJoinJoycon].DeviceType2;
		OnJoyShockDeviceConnected.Broadcast(DeviceInfo);
	}
	else if(ConnectedDeviceIds.Contains(_DeviceId))
	{
		SetPlayerIdByDeviceId(_DeviceId, _PlayerId);
	}
	else
	{
		FJoyShockDeviceEntry NewDevice;
		NewDevice.PlayerId = _PlayerId;
		NewDevice.DeviceId = _DeviceId;
		NewDevice.DeviceType = _DeviceType;

		Devices.Add(NewDevice);

		FJoyShockDeviceInfo DeviceInfo;
		DeviceInfo.PlayerId = NewDevice.PlayerId;
		DeviceInfo.DeviceId = NewDevice.DeviceId;
		DeviceInfo.DeviceType = NewDevice.DeviceType;
		OnJoyShockDeviceConnected.Broadcast(DeviceInfo);
	}
	SetPlayerNumberLight(_DeviceId, _DeviceType, _PlayerId + 1, _IndexToJoinJoycon >= 0);
	ConnectedDeviceIds.Add(_DeviceId);

}

void FJoyShockUnreal::RemoveRegisteredInputDeviceByDeviceId(int _DeviceId)
{
	bool bFound = false;
	int i = 0;
	while (i < Devices.Num() && !bFound)
	{
		bFound = (Devices[i].DeviceId == _DeviceId) || (Devices[i].bIsJoyconPair && Devices[i].DeviceId2 == _DeviceId);

		if (bFound)
		{
			if(Devices[i].bIsJoyconPair)
			{
				FJoyShockDeviceInfo DeviceInfo;
				DeviceInfo.PlayerId = Devices[i].PlayerId;
				DeviceInfo.bIsJoyconPair = Devices[i].bIsJoyconPair;

				if(Devices[i].DeviceId == _DeviceId)
				{
					DeviceInfo.DeviceId = Devices[i].DeviceId;
					DeviceInfo.DeviceType = Devices[i].DeviceType;

					Devices[i].DeviceId = Devices[i].DeviceId2;
					Devices[i].DeviceType = Devices[i].DeviceType2;
					Devices[i].LastButtonData = Devices[i].LastButtonData2;
				}
				else
				{
					DeviceInfo.DeviceId2 = Devices[i].DeviceId2;
					DeviceInfo.DeviceType2 = Devices[i].DeviceType2;
				}
				Devices[i].LastButtonData2 = 0;
				Devices[i].bIsJoyconPair = false;
				if (Devices[i].DeviceType == JS_TYPE_JOYCON_RIGHT)
				{
					SetPlayerNumberLight(Devices[i].DeviceId, Devices[i].DeviceType, Devices[i].PlayerId + 1, Devices[i].bIsJoyconPair);
				}
				OnJoyShockDeviceDisconnected.Broadcast(DeviceInfo);
			}
			else
			{
				FJoyShockDeviceInfo DeviceInfo;
				DeviceInfo.PlayerId = Devices[i].PlayerId;
				DeviceInfo.DeviceId = Devices[i].DeviceId;
				DeviceInfo.DeviceType = Devices[i].DeviceType;
				OnJoyShockDeviceDisconnected.Broadcast(DeviceInfo);
				Devices.RemoveAt(i);
			}
			ConnectedDeviceIds.Remove(_DeviceId);
		}
		++i;
	}
}


void FJoyShockUnreal::RemoveRegisteredInputDeviceByIndex(int _IndexToRemove)
{
	int DeviceId = Devices[_IndexToRemove].DeviceId;
	int DeviceId2 = Devices[_IndexToRemove].DeviceId2;

	Devices.RemoveAt(_IndexToRemove);
	ConnectedDeviceIds.Remove(DeviceId);
	ConnectedDeviceIds.Remove(DeviceId2);
}

void FJoyShockUnreal::SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler)
{
	MessageHandler = InMessageHandler;
}

void FJoyShockUnreal::HandleButtonPress(int _ButtonMask, int _ButtonData, int _LastButtonData, FName _KeyName, int _PlayerId)
{
	if ((_LastButtonData & _ButtonMask) != (_ButtonData & _ButtonMask))
	{
		if (_ButtonData & _ButtonMask)
		{
			MessageHandler->OnControllerButtonPressed(_KeyName, _PlayerId, false);
		}
		else
		{
			MessageHandler->OnControllerButtonReleased(_KeyName, _PlayerId, false);
		}
	}
	else if (_ButtonData & _ButtonMask)
	{
		MessageHandler->OnControllerButtonPressed(_KeyName, _PlayerId, true);
	}
}


void FJoyShockUnreal::HandleControllerEvents(int _PlayerId, int _DeviceId, int _DeviceType, bool _bIsJoyconPair, int& _LastButtonData)
{
	JOY_SHOCK_STATE SimpleState = JslGetSimpleState(_DeviceId);
	if (SimpleState.buttons != _LastButtonData)
	{
		int ButtonMask = 0x00001;
		if (_bIsJoyconPair || (_DeviceType != JS_TYPE_JOYCON_LEFT && _DeviceType != JS_TYPE_JOYCON_RIGHT))
		{
			for (int i = 0; i < NUM_BUTTONS; ++i)
			{
				HandleButtonPress(ButtonMask, SimpleState.buttons, _LastButtonData, ButtonMap[ButtonMask], _PlayerId);
				ButtonMask = ButtonMask << 1;
			}
		}
		switch (_DeviceType)
		{
		case JS_TYPE_JOYCON_LEFT:
			if (!_bIsJoyconPair)
			{
				HandleButtonPress(0x00008, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::Gamepad_FaceButton_Top, _PlayerId);
				HandleButtonPress(0x00004, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::Gamepad_FaceButton_Bottom, _PlayerId);
				HandleButtonPress(0x00001, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::Gamepad_FaceButton_Left, _PlayerId);
				HandleButtonPress(0x00002, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::Gamepad_FaceButton_Right, _PlayerId);
				HandleButtonPress(0x00040, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::Gamepad_LeftThumbstick, _PlayerId);
				HandleButtonPress(0x00100, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::Gamepad_LeftShoulder, _PlayerId);
				HandleButtonPress(0x00400, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::Gamepad_LeftTrigger, _PlayerId);
				HandleButtonPress(0x00020, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::Gamepad_Special_Right, _PlayerId);
				HandleButtonPress(0x400000, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::JoyShock_JoyconSL, _PlayerId);
				HandleButtonPress(0x800000, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::JoyShock_JoyconSR, _PlayerId);
			}
			else
			{
				HandleButtonPress(0x400000, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::JoyShock_LeftJoyconSL, _PlayerId);
				HandleButtonPress(0x800000, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::JoyShock_LeftJoyconSR, _PlayerId);
			}
			
			HandleButtonPress(0x200000, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::JoyShock_SwitchCapture, _PlayerId);
			break;
		case JS_TYPE_JOYCON_RIGHT:
			if (!_bIsJoyconPair)
			{
				HandleButtonPress(0x04000, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::Gamepad_FaceButton_Top, _PlayerId);
				HandleButtonPress(0x02000, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::Gamepad_FaceButton_Bottom, _PlayerId);
				HandleButtonPress(0x01000, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::Gamepad_FaceButton_Left, _PlayerId);
				HandleButtonPress(0x08000, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::Gamepad_FaceButton_Right, _PlayerId);
				HandleButtonPress(0x00080, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::Gamepad_LeftThumbstick, _PlayerId);
				HandleButtonPress(0x00200, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::Gamepad_RightShoulder, _PlayerId);
				HandleButtonPress(0x00800, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::Gamepad_RightTrigger, _PlayerId);
				HandleButtonPress(0x00010, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::Gamepad_Special_Right, _PlayerId);
				HandleButtonPress(0x400000, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::JoyShock_JoyconSL, _PlayerId);
				HandleButtonPress(0x800000, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::JoyShock_JoyconSR, _PlayerId);
			}
			else
			{
				HandleButtonPress(0x400000, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::JoyShock_RightJoyconSL, _PlayerId);
				HandleButtonPress(0x800000, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::JoyShock_RightJoyconSR, _PlayerId);
			}

			break;
		case JS_TYPE_PRO_CONTROLLER:
			HandleButtonPress(0x200000, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::JoyShock_SwitchCapture, _PlayerId);
		case JS_TYPE_DS4:
			HandleButtonPress(0x200000, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::JoyShock_TouchpadPress, _PlayerId);
		case JS_TYPE_DS:
			HandleButtonPress(0x200000, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::JoyShock_DualsenseCreate, _PlayerId);
			HandleButtonPress(0x400000, SimpleState.buttons, _LastButtonData, FJoyShockKeyNames::JoyShock_DualsenseMic, _PlayerId);
		}
		_LastButtonData = SimpleState.buttons;
	}
	if (!_bIsJoyconPair && (_DeviceType == JS_TYPE_JOYCON_LEFT || _DeviceType == JS_TYPE_JOYCON_RIGHT))
	{
		if (_DeviceType == JS_TYPE_JOYCON_LEFT)
		{
			const float AuxStickX = SimpleState.stickLX;
			SimpleState.stickLX = -SimpleState.stickLY;
			SimpleState.stickLY = AuxStickX;
		}
		if (_DeviceType == JS_TYPE_JOYCON_RIGHT)
		{
			SimpleState.stickLX = SimpleState.stickRY;
			SimpleState.stickLY = -SimpleState.stickRX;

			SimpleState.stickRX = 0.f;
			SimpleState.stickRY = 0.f;
		}
	}
	if (_DeviceType != JS_TYPE_JOYCON_RIGHT || !_bIsJoyconPair)
	{
		MessageHandler->OnControllerAnalog(FJoyShockKeyNames::Gamepad_LeftX, _PlayerId, SimpleState.stickLX);
		MessageHandler->OnControllerAnalog(FJoyShockKeyNames::Gamepad_LeftY, _PlayerId, SimpleState.stickLY);
		MessageHandler->OnControllerAnalog(FJoyShockKeyNames::Gamepad_LeftTriggerAxis, _PlayerId, SimpleState.lTrigger);
	}
	if (_DeviceType != JS_TYPE_JOYCON_LEFT)
	{
		MessageHandler->OnControllerAnalog(FJoyShockKeyNames::Gamepad_RightX, _PlayerId, SimpleState.stickRX);
		MessageHandler->OnControllerAnalog(FJoyShockKeyNames::Gamepad_RightY, _PlayerId, SimpleState.stickRY);
		MessageHandler->OnControllerAnalog(FJoyShockKeyNames::Gamepad_RightTriggerAxis, _PlayerId, SimpleState.rTrigger);
	}
	if (_DeviceType == JS_TYPE_DS || _DeviceType == JS_TYPE_DS4)
	{
		TOUCH_STATE TouchState = JslGetTouchState(_DeviceId);

		if (TouchState.t0Down)
		{
			MessageHandler->OnControllerButtonPressed(FJoyShockKeyNames::JoyShock_FirstPressTouchpad, _PlayerId, false);
			MessageHandler->OnControllerAnalog(FJoyShockKeyNames::JoyShock_FirstPressTouchpadX, _PlayerId, TouchState.t0X);
			MessageHandler->OnControllerAnalog(FJoyShockKeyNames::JoyShock_FirstPressTouchpadY, _PlayerId, TouchState.t0Y);
		}
		else
		{
			MessageHandler->OnControllerButtonReleased(FJoyShockKeyNames::JoyShock_FirstPressTouchpad, _PlayerId, false);
		}
		if (TouchState.t1Down)
		{
			MessageHandler->OnControllerButtonPressed(FJoyShockKeyNames::JoyShock_SecondPressTouchpad, _PlayerId, false);
			MessageHandler->OnControllerAnalog(FJoyShockKeyNames::JoyShock_SecondPressTouchpadX, _PlayerId, TouchState.t1X);
			MessageHandler->OnControllerAnalog(FJoyShockKeyNames::JoyShock_SecondPressTouchpadY, _PlayerId, TouchState.t1Y);
		}
		else
		{
			MessageHandler->OnControllerButtonReleased(FJoyShockKeyNames::JoyShock_SecondPressTouchpad, _PlayerId, false);
		}
	}

	IMU_STATE ImuState = JslGetIMUState(_DeviceId);
	MOTION_STATE MotionState = JslGetMotionState(_DeviceId);

	FVector Orientation = FQuat(MotionState.quatZ, -MotionState.quatX, MotionState.quatY, -MotionState.quatW).Euler();
	if (_bIsJoyconPair && _DeviceType == JS_TYPE_JOYCON_LEFT)
	{
		MessageHandler->OnControllerAnalog(FJoyShockKeyNames::JoyShock_LeftJoyconGyroX, _PlayerId, ImuState.gyroX);
		MessageHandler->OnControllerAnalog(FJoyShockKeyNames::JoyShock_LeftJoyconGyroY, _PlayerId, ImuState.gyroY);
		MessageHandler->OnControllerAnalog(FJoyShockKeyNames::JoyShock_LeftJoyconGyroZ, _PlayerId, ImuState.gyroZ);

		MessageHandler->OnControllerAnalog(FJoyShockKeyNames::JoyShock_LeftJoyconAccelX, _PlayerId, ImuState.accelX);
		MessageHandler->OnControllerAnalog(FJoyShockKeyNames::JoyShock_LeftJoyconAccelY, _PlayerId, ImuState.accelY);
		MessageHandler->OnControllerAnalog(FJoyShockKeyNames::JoyShock_LeftJoyconAccelZ, _PlayerId, ImuState.accelZ);

		MessageHandler->OnControllerAnalog(FJoyShockKeyNames::JoyShock_LeftJoyconOrientationX, _PlayerId, Orientation.X);
		MessageHandler->OnControllerAnalog(FJoyShockKeyNames::JoyShock_LeftJoyconOrientationY, _PlayerId, Orientation.Y);
		MessageHandler->OnControllerAnalog(FJoyShockKeyNames::JoyShock_LeftJoyconOrientationZ, _PlayerId, Orientation.Z);
	}
	else
	{
		if (!_bIsJoyconPair)
		{
			if (_DeviceType == JS_TYPE_JOYCON_LEFT)
			{
				float AuxOrientationX = Orientation.X;
				Orientation.X = Orientation.Y;
				Orientation.Y = -AuxOrientationX;
			}
			else if (_DeviceType == JS_TYPE_JOYCON_RIGHT)
			{
				float AuxOrientationX = Orientation.X;
				Orientation.X = -Orientation.Y;
				Orientation.Y = AuxOrientationX;
			}

		}

		MessageHandler->OnMotionDetected(Orientation, FVector(ImuState.gyroZ, -ImuState.gyroX, ImuState.gyroY),
			FVector(MotionState.gravZ, -MotionState.gravX, MotionState.gravY),
			FVector(ImuState.accelY, -ImuState.accelX, ImuState.accelY), _PlayerId);
	}
}

void FJoyShockUnreal::Tick(float DeltaTime)
{

}

void FJoyShockUnreal::SendControllerEvents()
{
	for (FJoyShockDeviceEntry& Device: Devices)
	{
		HandleControllerEvents(Device.PlayerId, Device.DeviceId, Device.DeviceType, Device.bIsJoyconPair, Device.LastButtonData);
		if(Device.bIsJoyconPair)
		{
			HandleControllerEvents(Device.PlayerId, Device.DeviceId2, Device.DeviceType2, Device.bIsJoyconPair, Device.LastButtonData2);
		}
	}
}

void FJoyShockUnreal::SetChannelValue(int32 PlayerId, FForceFeedbackChannelType ChannelType, float Value)
{
	TPair<int, int> DeviceId = GetDeviceIdByPlayerId(PlayerId);
	if(ChannelType == FForceFeedbackChannelType::LEFT_LARGE)
	{
		JslSetRumble(DeviceId.Key, Value * 255, 0);
		JslSetRumble(DeviceId.Value, Value * 255, 0);
	}
	else if(ChannelType == FForceFeedbackChannelType::RIGHT_LARGE)
	{
		JslSetRumble(DeviceId.Key, 0, Value * 255);
		JslSetRumble(DeviceId.Value, 0, Value * 255);
	}
}

void FJoyShockUnreal::SetChannelValues(int32 PlayerId, const FForceFeedbackValues& Values)
{
	if (Values.LeftLarge == LastForceFeedbackValues.LeftLarge && Values.RightLarge == LastForceFeedbackValues.RightLarge)
	{
		RepeatForceFeedbackTimer += FApp::GetDeltaTime();
		if (RepeatForceFeedbackTimer < RepeatForceFeedbackTime) return;
	}

	RepeatForceFeedbackTimer = 0.f;
	LastForceFeedbackValues = Values;

	TPair<int, int> DeviceId = GetDeviceIdByPlayerId(PlayerId);

	JslSetRumble(DeviceId.Key, Values.LeftLarge * 255, Values.RightLarge * 255);
	JslSetRumble(DeviceId.Value, Values.LeftLarge * 255, Values.RightLarge * 255);
}


bool FJoyShockUnreal::SupportsForceFeedback(int32 ControllerId)
{
	TPair<int, int> DeviceId = GetDeviceIdByPlayerId(ControllerId);

	int ControllerType = JslGetControllerType(DeviceId.Key);
	return ControllerType != JS_TYPE_JOYCON_LEFT && ControllerType != JS_TYPE_JOYCON_RIGHT && ControllerType != JS_TYPE_PRO_CONTROLLER;
}

bool FJoyShockUnreal::JoinJoyconsByDeviceId(int _DeviceId, int _DeviceId2)
{
	bool bIsValid = false;
	int Index = -1;
	int Index2 = -1;
	int i = 0; 
	while (i < Devices.Num() && (Index == -1 || Index2 == -1))
	{
		if(Devices[i].DeviceId == _DeviceId)
		{
			Index = i;
		}
		else if(Devices[i].DeviceId == _DeviceId2)
		{
			Index2 = i;
		}

		if (Index != -1 && Index2 != -1)
		{
			int DeviceType2 = JslGetControllerType(_DeviceId2);
			bIsValid = (Devices[Index].DeviceType == JS_TYPE_JOYCON_LEFT && DeviceType2 == JS_TYPE_JOYCON_RIGHT) ||
				(Devices[Index].DeviceType == JS_TYPE_JOYCON_RIGHT && DeviceType2 == JS_TYPE_JOYCON_LEFT) && !Devices[Index].bIsJoyconPair && !Devices[Index2].bIsJoyconPair;
			if (bIsValid)
			{
				RegisterInputDevice(Devices[Index].PlayerId, _DeviceId2, DeviceType2, Index);
				SetPlayerNumberLight(Devices[Index].DeviceId, Devices[Index].DeviceType, Devices[Index].PlayerId + 1, Devices[Index].bIsJoyconPair);
			}
		}
		++i;
	}

	return bIsValid;
}


bool FJoyShockUnreal::JoinJoyconsByControllerId(int _ControllerId, int _ControllerId2)
{
	bool bIsValid = false;
	int Index = -1;
	int Index2 = -1;
	int i = 0;
	while (i < Devices.Num() && (Index == -1 || Index2 == -1))
	{
		if (Devices[i].PlayerId == _ControllerId)
		{
			Index = i;
		}
		else if (Devices[i].PlayerId == _ControllerId2)
		{
			Index2 = i;
		}

		if (Index != -1 && Index2 != -1)
		{
			int DeviceType2 = JslGetControllerType(Devices[Index2].DeviceId);
			bIsValid = (Devices[Index].DeviceType == JS_TYPE_JOYCON_LEFT && DeviceType2 == JS_TYPE_JOYCON_RIGHT) ||
				(Devices[Index].DeviceType == JS_TYPE_JOYCON_RIGHT && DeviceType2 == JS_TYPE_JOYCON_LEFT) && !Devices[Index].bIsJoyconPair && !Devices[Index2].bIsJoyconPair;
			if (bIsValid)
			{
				RegisterInputDevice(Devices[Index].PlayerId, Devices[Index2].DeviceId, DeviceType2, Index);
				SetPlayerNumberLight(Devices[Index].DeviceId, Devices[Index].DeviceType, Devices[Index].PlayerId + 1, Devices[Index].bIsJoyconPair);
			}
		}
		++i;
	}

	return bIsValid;
}


void FJoyShockUnreal::SetPlayerNumberLight(int _DeviceId, int _DeviceType, int _PlayerNumber, bool _bIsJoyconPair)
{
	if (_DeviceType == JS_TYPE_JOYCON_RIGHT && !_bIsJoyconPair)
	{
		JslSetPlayerNumber(_DeviceId, 0x8 >> (_PlayerNumber - 1));
	}
	else if(_DeviceType == JS_TYPE_DS)
	{
		int PlayerNumberMask = 0;
		switch(_PlayerNumber)
		{
		case 1:
			PlayerNumberMask = DS5_PLAYER_1;
			break;
		case 2:
			PlayerNumberMask = DS5_PLAYER_2;
			break;
		case 3:
			PlayerNumberMask = DS5_PLAYER_3;
			break;
		case 4:
			PlayerNumberMask = DS5_PLAYER_4;
			break;
		case 5:
			PlayerNumberMask = DS5_PLAYER_5;
			break;
		}
		JslSetPlayerNumber(_DeviceId, PlayerNumberMask);
	}
	else
	{
		JslSetPlayerNumber(_DeviceId, _PlayerNumber);
	}
}

TPair<int, int> FJoyShockUnreal::GetDeviceIdByPlayerId(int _PlayerId) const
{
	bool bFound = false;
	int i = 0;
	TPair<int, int> DeviceId;
	DeviceId.Key = -1;
	DeviceId.Value = -1;

	while (i < Devices.Num() && !bFound)
	{
		bFound = Devices[i].PlayerId == _PlayerId;

		if (bFound)
		{
			DeviceId.Key = Devices[i].DeviceId;
			DeviceId.Value = Devices[i].DeviceId2;

		}
		++i;
	}

	return DeviceId;
}


void FJoyShockUnreal::SetPlayerIdByDeviceId(int _DeviceId, int _PlayerId)
{
	bool bFound = false;
	int i = 0;

	while (i < Devices.Num() && !bFound)
	{
		bFound = Devices[i].DeviceId == _DeviceId || Devices[i].DeviceId2 == _DeviceId;

		if (bFound)
		{
			Devices[i].PlayerId = _PlayerId;
		}
		++i;
	}
}

int FJoyShockUnreal::GetIndexByDeviceId(int _DeviceId)
{
	bool bFound = false;
	int Result = -1;
	int i = 0;
	while (i < Devices.Num() && !bFound)
	{
		bFound = (Devices[i].DeviceId == _DeviceId) || (Devices[i].bIsJoyconPair && Devices[i].DeviceId2 == _DeviceId);

		if (bFound)
		{
			Result = i;
		}
		++i;
	}

	return Result;
}


int FJoyShockUnreal::GetNumJoyShockDevices()
{
	return ConnectedDevices;
}


int FJoyShockUnreal::GetNumJoyShockPlayers()
{
	return Devices.Num();
}

TSharedPtr<class IInputDevice> FJoyShockUnrealPlugin::CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
#if PLATFORM_WINDOWS
	JoyShockDevice = MakeShareable(new FJoyShockUnrealWindows(InMessageHandler));
#else
	JoyShockDevice = MakeShareable(new FJoyShockUnreal(InMessageHandler));
#endif
	return JoyShockDevice;
}


void FJoyShockUnrealPlugin::StartupModule()
{

	FString BaseDir = IPluginManager::Get().FindPlugin("JoyShockUnreal")->GetBaseDir();


#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
	LibraryPath = FPaths::Combine(
		*BaseDir,
		TEXT("Source/ThirdParty/JoyShockLibrary/Debug/JoyShockLibrary.dll"));
#else
	FString LibraryPath;
	LibraryPath = FPaths::Combine(
		*BaseDir,
		TEXT("Source/ThirdParty/JoyShockLibrary/Release/JoyShockLibrary.dll"));
#endif
	// Getting the handle to the DLL methods
	JoyShockHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;
	if (JoyShockHandle)
	{
		// Do something when the DLL is first loaded
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load DualSense third party library"));
	}

	IInputDeviceModule::StartupModule();

	const FName NAME_JoyShock(TEXT("JoyShock"));

	EKeys::AddMenuCategoryDisplayInfo(NAME_JoyShock, LOCTEXT("JoyShockSubCategory", "JoyShock"), TEXT("GraphEditor.PadEvent_16x"));

	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_SwitchCapture, LOCTEXT("JoyShock_SwitchCapture", "JoyShock Switch Capture"), FKeyDetails::GamepadKey, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_Home, LOCTEXT("JoyShock_Home", "JoyShock Home"), FKeyDetails::GamepadKey, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_TouchpadPress, LOCTEXT("JoyShock_TouchpadPress", "JoyShock Touchpad Press"), FKeyDetails::GamepadKey, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_LeftJoyconSL, LOCTEXT("JoyShock_LeftJoyconSL", "JoyShock Left Joycon SL"), FKeyDetails::GamepadKey, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_LeftJoyconSR, LOCTEXT("JoyShock_LeftJoyconSR", "JoyShock Left Joycon SR"), FKeyDetails::GamepadKey, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_RightJoyconSL, LOCTEXT("JoyShock_RightJoyconSL", "JoyShock Right Joycon SL"), FKeyDetails::GamepadKey, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_RightJoyconSR, LOCTEXT("JoyShock_RightJoyconSR", "JoyShock Right Joycon SR"), FKeyDetails::GamepadKey, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_JoyconSL, LOCTEXT("JoyShock_JoyconSL", "JoyShock Joycon SL"), FKeyDetails::GamepadKey, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_JoyconSR, LOCTEXT("JoyShock_JoyconSR", "JoyShock Joycon SR"), FKeyDetails::GamepadKey, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_DualsenseCreate, LOCTEXT("JoyShock_DualsenseCreate", "JoyShock Dualsense Create"), FKeyDetails::GamepadKey, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_DualsenseMic, LOCTEXT("JoyShock_DualsenseMic", "JoyShock Dualsense Mic"), FKeyDetails::GamepadKey, NAME_JoyShock));

	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_FirstPressTouchpad, LOCTEXT("JoyShock_FirstPressTouchpad", "JoyShock First Press Touchpad"), FKeyDetails::GamepadKey, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_FirstPressTouchpadX, LOCTEXT("JoyShock_FirstPressTouchpadX", "JoyShock First Press Touchpad X-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_FirstPressTouchpadY, LOCTEXT("JoyShock_FirstPressTouchpadY", "JoyShock First Press Touchpad Y-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D, NAME_JoyShock));
	EKeys::AddPairedKey(FKeyDetails(FJoyShockKeys::JoyShock_FirstPressTouchpad2D, LOCTEXT("JoyShock_FirstPressTouchpad2D", "JoyShock First Press Touchpad 2D-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis2D, NAME_JoyShock),
		FJoyShockKeys::JoyShock_FirstPressTouchpadX, FJoyShockKeys::JoyShock_FirstPressTouchpadY);
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_SecondPressTouchpad, LOCTEXT("JoyShock_SecondPressTouchpad", "JoyShock Second Press Touchpad"), FKeyDetails::GamepadKey, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_SecondPressTouchpadX, LOCTEXT("JoyShock_SecondPressTouchpadX", "JoyShock Second Press Touchpad X-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_SecondPressTouchpadY, LOCTEXT("JoyShock_SecondPressTouchpadY", "JoyShock Second Press Touchpad Y-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D, NAME_JoyShock));
	EKeys::AddPairedKey(FKeyDetails(FJoyShockKeys::JoyShock_SecondPressTouchpad2D, LOCTEXT("JoyShock_SecondPressTouchpad2D", "JoyShock Second Press Touchpad 2D-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis2D, NAME_JoyShock),
		FJoyShockKeys::JoyShock_SecondPressTouchpadX, FJoyShockKeys::JoyShock_SecondPressTouchpadY);
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_LeftJoyconAccelX, LOCTEXT("JoyShock_LeftJoyconAccelX", "JoyShock Left Joycon Accel X-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_LeftJoyconAccelY, LOCTEXT("JoyShock_LeftJoyconAccelY", "JoyShock Left Joycon Accel Y-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_LeftJoyconAccelZ, LOCTEXT("JoyShock_LeftJoyconAccelZ", "JoyShock Left Joycon Accel Z-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_LeftJoyconAccel3D, LOCTEXT("JoyShock_LeftJoyconAccel3D", "JoyShock Left Joycon Accel 3D-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis3D, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_LeftJoyconGyroX, LOCTEXT("JoyShock_LeftJoyconGyroX", "JoyShock Left Joycon Gyro X-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_LeftJoyconGyroY, LOCTEXT("JoyShock_LeftJoyconGyroY", "JoyShock Left Joycon Gyro Y-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_LeftJoyconGyroZ, LOCTEXT("JoyShock_LeftJoyconGyroZ", "JoyShock Left Joycon Gyro Z-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_LeftJoyconGyro3D, LOCTEXT("JoyShock_LeftJoyconGyro3D", "JoyShock Left Joycon Gyro 3D-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis3D, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_LeftJoyconOrientationX, LOCTEXT("JoyShock_LeftJoyconOrientationX", "JoyShock Left Joycon Orientation X-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_LeftJoyconOrientationY, LOCTEXT("JoyShock_LeftJoyconOrientationY", "JoyShock Left Joycon Orientation Y-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D, NAME_JoyShock));
	EKeys::AddKey(FKeyDetails(FJoyShockKeys::JoyShock_LeftJoyconOrientationZ, LOCTEXT("JoyShock_LeftJoyconOrientationZ", "JoyShock Left Joycon Orientation Z-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D, NAME_JoyShock));

}

IMPLEMENT_MODULE(FJoyShockUnrealPlugin, JoyShockUnreal)

//#undef LOCTEXT_NAMESPACE

void FJoyShockUnrealPlugin::ShutdownModule()
{
	FPlatformProcess::FreeDllHandle(JoyShockHandle);
	JoyShockHandle = nullptr;
}
