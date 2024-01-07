// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GenericPlatform/GenericApplicationMessageHandler.h"
#include <JoyShockUnreal.h>
#include "JoyShockUnrealFunctionLibrary.generated.h"


struct JOYSHOCKUNREAL_API FJoyShockKeyNames
{
	static const FGamepadKeyNames::Type Gamepad_LeftX;
	static const FGamepadKeyNames::Type Gamepad_LeftY;
	static const FGamepadKeyNames::Type Gamepad_RightX;
	static const FGamepadKeyNames::Type Gamepad_RightY;
	static const FGamepadKeyNames::Type Gamepad_LeftTriggerAxis;
	static const FGamepadKeyNames::Type Gamepad_RightTriggerAxis;

	static const FGamepadKeyNames::Type Gamepad_DPad_Up;
	static const FGamepadKeyNames::Type Gamepad_DPad_Down;
	static const FGamepadKeyNames::Type Gamepad_DPad_Right;
	static const FGamepadKeyNames::Type Gamepad_DPad_Left;
	static const FGamepadKeyNames::Type Gamepad_Special_Right;
	static const FGamepadKeyNames::Type Gamepad_Special_Left;
	static const FGamepadKeyNames::Type Gamepad_LeftThumbstick;
	static const FGamepadKeyNames::Type Gamepad_RightThumbstick;
	static const FGamepadKeyNames::Type Gamepad_LeftShoulder;
	static const FGamepadKeyNames::Type Gamepad_RightShoulder;
	static const FGamepadKeyNames::Type Gamepad_LeftTrigger;
	static const FGamepadKeyNames::Type Gamepad_RightTrigger;
	static const FGamepadKeyNames::Type Gamepad_FaceButton_Bottom;
	static const FGamepadKeyNames::Type Gamepad_FaceButton_Left;
	static const FGamepadKeyNames::Type Gamepad_FaceButton_Right;
	static const FGamepadKeyNames::Type Gamepad_FaceButton_Top;

	static const FGamepadKeyNames::Type JoyShock_SwitchCapture;
	static const FGamepadKeyNames::Type JoyShock_Home;
	static const FGamepadKeyNames::Type JoyShock_TouchpadPress;
	static const FGamepadKeyNames::Type JoyShock_LeftJoyconSL;
	static const FGamepadKeyNames::Type JoyShock_LeftJoyconSR;
	static const FGamepadKeyNames::Type JoyShock_RightJoyconSL;
	static const FGamepadKeyNames::Type JoyShock_RightJoyconSR;
	static const FGamepadKeyNames::Type JoyShock_JoyconSL;
	static const FGamepadKeyNames::Type JoyShock_JoyconSR;
	static const FGamepadKeyNames::Type JoyShock_DualsenseCreate;
	static const FGamepadKeyNames::Type JoyShock_DualsenseMic;

	static const FGamepadKeyNames::Type JoyShock_FirstPressTouchpad;
	static const FGamepadKeyNames::Type JoyShock_FirstPressTouchpadX;
	static const FGamepadKeyNames::Type JoyShock_FirstPressTouchpadY;
	static const FGamepadKeyNames::Type JoyShock_FirstPressTouchpad2D;
	static const FGamepadKeyNames::Type JoyShock_SecondPressTouchpad;
	static const FGamepadKeyNames::Type JoyShock_SecondPressTouchpadX;
	static const FGamepadKeyNames::Type JoyShock_SecondPressTouchpadY;
	static const FGamepadKeyNames::Type JoyShock_SecondPressTouchpad2D;

	static const FGamepadKeyNames::Type JoyShock_LeftJoyconAccelX;
	static const FGamepadKeyNames::Type JoyShock_LeftJoyconAccelY;
	static const FGamepadKeyNames::Type JoyShock_LeftJoyconAccelZ;
	static const FGamepadKeyNames::Type JoyShock_LeftJoyconAccel3D;
	static const FGamepadKeyNames::Type JoyShock_LeftJoyconGyroX;
	static const FGamepadKeyNames::Type JoyShock_LeftJoyconGyroY;
	static const FGamepadKeyNames::Type JoyShock_LeftJoyconGyroZ;
	static const FGamepadKeyNames::Type JoyShock_LeftJoyconGyro3D;
	static const FGamepadKeyNames::Type JoyShock_LeftJoyconOrientationX;
	static const FGamepadKeyNames::Type JoyShock_LeftJoyconOrientationY;
	static const FGamepadKeyNames::Type JoyShock_LeftJoyconOrientationZ;
};

struct JOYSHOCKUNREAL_API FJoyShockKeys
{
  static const FKey JoyShock_SwitchCapture;
  static const FKey JoyShock_Home;
  static const FKey JoyShock_TouchpadPress;
  static const FKey JoyShock_LeftJoyconSL;
  static const FKey JoyShock_LeftJoyconSR;
  static const FKey JoyShock_RightJoyconSL;
  static const FKey JoyShock_RightJoyconSR;
  static const FKey JoyShock_JoyconSL;
  static const FKey JoyShock_JoyconSR;
  static const FKey JoyShock_DualsenseCreate;
  static const FKey JoyShock_DualsenseMic;

  static const FKey JoyShock_FirstPressTouchpad;
  static const FKey JoyShock_FirstPressTouchpadX;
	static const FKey JoyShock_FirstPressTouchpadY;
	static const FKey JoyShock_FirstPressTouchpad2D;
  static const FKey JoyShock_SecondPressTouchpad;
  static const FKey JoyShock_SecondPressTouchpadX;
	static const FKey JoyShock_SecondPressTouchpadY;
	static const FKey JoyShock_SecondPressTouchpad2D;

	static const FKey JoyShock_LeftJoyconAccelX;
	static const FKey JoyShock_LeftJoyconAccelY;
	static const FKey JoyShock_LeftJoyconAccelZ;
	static const FKey JoyShock_LeftJoyconAccel3D;
	static const FKey JoyShock_LeftJoyconGyroX;
	static const FKey JoyShock_LeftJoyconGyroY;
	static const FKey JoyShock_LeftJoyconGyroZ;
	static const FKey JoyShock_LeftJoyconGyro3D;
	static const FKey JoyShock_LeftJoyconOrientationX;
	static const FKey JoyShock_LeftJoyconOrientationY;
	static const FKey JoyShock_LeftJoyconOrientationZ;

};



USTRUCT(BlueprintType)
struct JOYSHOCKUNREAL_API FJoyShockControllerColor
{
	GENERATED_BODY()
		
	UPROPERTY(BlueprintReadOnly, Category = "RawInput")
	FColor BodyColor;
	UPROPERTY(BlueprintReadOnly, Category = "RawInput")
	FColor LeftButtonColor;
	UPROPERTY(BlueprintReadOnly, Category = "RawInput")
	FColor RightButtonColor;
	UPROPERTY(BlueprintReadOnly, Category = "RawInput")
	FColor LeftGripColor;
	UPROPERTY(BlueprintReadOnly, Category = "RawInput")
	FColor RightGripColor;

};


UCLASS()
class JOYSHOCKUNREAL_API UJoyShockFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="JoyShock")
	static TArray<FJoyShockDeviceInfo> GetRegisteredDevices();
	
	UFUNCTION(BlueprintPure, Category="JoyShock")
	static FJoyShockControllerColor GetControllerColorsByControllerId(int _ControllerId);
	
	UFUNCTION(BlueprintPure, Category="JoyShock")
	static FJoyShockControllerColor GetControllerColorsByDeviceId(int _ControllerId);
	
	UFUNCTION(BlueprintPure, Category="JoyShock")
	static void SetControllerLightColorByDeviceId(int _DeviceId, const FColor& _Color);
	
	UFUNCTION(BlueprintPure, Category="JoyShock")
	static void SetControllerLightColorByControllerId(int _ControllerId, const FColor& _Color);
	
	UFUNCTION(BlueprintPure, Category="JoyShock")
	static bool JoinJoyconsByDeviceId(int _DeviceId, int _DeviceId2);
	
	UFUNCTION(BlueprintPure, Category="JoyShock")
	static bool JoinJoyconsByControllerId(int _ControllerId, int _ControllerId2);
	
	UFUNCTION(BlueprintPure, Category="JoyShock")
	static bool QueryConnectedDevices();

	UFUNCTION(BlueprintPure, Category="JoyShock")
	static bool DisconnectAllDevices();
	
	UFUNCTION(BlueprintPure, Category = "JoyShock")
	static void GetDeviceIdByPlayerId(int _PlayerId, int& DeviceId_, int& DeviceId2_);

	UFUNCTION(BlueprintPure, Category = "JoyShock")
	static bool SetPlayerIdByDeviceId(int _DeviceId, int _PlayerId);

	UFUNCTION(BlueprintPure, Category = "JoyShock")
	static int GetNumJoyShockDevices();
	
	UFUNCTION(BlueprintPure, Category = "JoyShock")
	static int GetNumJoyShockPlayers();
	
	static FOnJoyShockDeviceConnected* GetOnDeviceConnectedDelegate();
	static FOnJoyShockDeviceDisconnected* GetOnDeviceDisconnectedDelegate();

private:
	static FJoyShockControllerColor IntToControllerColor(int _BodyColor, int _LeftButtonColor, int _RightButtonColor, int _LeftGripColor, int _RightGripColor);
};

