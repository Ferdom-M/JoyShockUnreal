// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "IInputDeviceModule.h"
#include "IInputDevice.h"
#include "JoyShockDeviceInfo.h"
#include "GenericPlatform/GenericApplicationMessageHandler.h"

struct FJoyShockDeviceEntry
{
	bool bIsJoyconPair = false;

	int PlayerId = -1;

	int DeviceId = -1;
	int DeviceType = -1;
	int LastButtonData = 0x000000;

	int DeviceId2 = -1;
	int DeviceType2 = -1;
	int LastButtonData2 = 0x000000;

	inline bool operator==(const FJoyShockDeviceEntry& _Other) { return DeviceId == _Other.DeviceId; }
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnJoyShockDeviceConnected, FJoyShockDeviceInfo);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnJoyShockDeviceDisconnected, FJoyShockDeviceInfo);

class FJoyShockUnreal : public IInputDevice
{
public:
	FJoyShockUnreal(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);

	virtual ~FJoyShockUnreal() {}

	void QueryConnectedDevices();
	void DisconnectAllDevices();
	void RegisterInputDevice(int _PlayerId, int _DeviceId, int _DeviceType, int _DeviceIdToJoinJoycon = -1);
	void RemoveRegisteredInputDeviceByDeviceId(int _DeviceId);
	void RemoveRegisteredInputDeviceByIndex(int _IndexToRemove);
	void SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler);
	void HandleButtonPress(int _ButtonMask, int _ButtonData, int _LastButtonData, FName _KeyName, int _PlayerId);
	void HandleControllerEvents(int _PlayerId, int _DeviceId, int _DeviceType, bool _bIsJoyconPair, int& _LastButtonData);

	virtual void Tick(float DeltaTime) override;
	virtual void SendControllerEvents() override;
	virtual void SetChannelValue(int32 PlayerId, FForceFeedbackChannelType ChannelType, float Value) override;
	virtual void SetChannelValues(int32 PlayerId, const FForceFeedbackValues& Values) override;
	virtual bool SupportsForceFeedback(int32 ControllerId) override;
	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override { return false; }
	virtual bool IsGamepadAttached() const override { return ConnectedDevices > 0; }

	bool JoinJoyconsByDeviceId(int _DeviceId, int _DeviceId2);
	bool JoinJoyconsByControllerId(int _ControllerId, int _ControllerId2);

	void SetPlayerNumberLight(int _DeviceId, int _DeviceType, int _PlayerNumber, bool _bIsJoyconPair);

	const TArray<FJoyShockDeviceEntry>& GetDevices() const { return Devices; }
	TPair<int, int> GetDeviceIdByPlayerId(int _PlayerId) const;
	void SetPlayerIdByDeviceId(int _DeviceId, int _PlayerId);
	int GetIndexByDeviceId(int _DeviceId);
	int GetNumJoyShockDevices();
	int GetNumJoyShockPlayers();

	FOnJoyShockDeviceConnected OnJoyShockDeviceConnected;
	FOnJoyShockDeviceDisconnected OnJoyShockDeviceDisconnected;
protected:

	/** Delegate to allow for manual parsing of HID data. */
	//FRawInputDataDelegate DataReceivedHandler;

	/** Handler to send all messages to. */
	TSharedRef<FGenericApplicationMessageHandler> MessageHandler;

	/** Helper to get next input handle to assign. */
	int32 GetNextInputHandle() { return LastAssignedInputHandle++; }

private:

	int32 LastAssignedInputHandle;

	TMap<int, FName> ButtonMap;
	TArray<FJoyShockDeviceEntry> Devices;
	TSet<int> ConnectedDeviceIds;
	int ConnectedDevices = 0;

	const int NUM_BUTTONS = 17;
	
	FForceFeedbackValues LastForceFeedbackValues;

	float RepeatForceFeedbackTimer = 0.f;
	const float RepeatForceFeedbackTime = 4.f;
};

class FJoyShockUnrealPlugin : public IInputDeviceModule
{
	virtual TSharedPtr<class IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;

	TSharedPtr<class FJoyShockUnreal> JoyShockDevice;

public:
	TSharedPtr<class FJoyShockUnreal>& GetJoyShockDevice() { return JoyShockDevice; }

	virtual void StartupModule() override;

	virtual void ShutdownModule() override;

	static inline FJoyShockUnrealPlugin& Get()
	{
		return FModuleManager::LoadModuleChecked<FJoyShockUnrealPlugin>("JoyShockUnreal");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("JoyShockUnreal");
	}
};


void* JoyShockHandle = nullptr;