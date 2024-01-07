#pragma once

#include "CoreMinimal.h"
#include "JoyShockDeviceInfo.generated.h"

USTRUCT(BlueprintType)
struct JOYSHOCKUNREAL_API FJoyShockDeviceInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "JoyShock")
	bool bIsJoyconPair = false;

	UPROPERTY(BlueprintReadOnly, Category = "JoyShock")
	int PlayerId = -1;

	UPROPERTY(BlueprintReadOnly, Category = "JoyShock")
	int DeviceId = -1;

	UPROPERTY(BlueprintReadOnly, Category = "JoyShock")
	int DeviceType = -1;

	UPROPERTY(BlueprintReadOnly, Category = "JoyShock")
	int DeviceId2 = -1;

	UPROPERTY(BlueprintReadOnly, Category = "JoyShock")
	int DeviceType2 = -1;
};