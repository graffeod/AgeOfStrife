// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/UserDefinedEnum.h"
#include "VehicleMovementStateEnum.generated.h"

UENUM(BlueprintType)
enum class EVehicleMovementState : uint8 {
	VMS_Idle UMETA(DisplayName = "Idle"),
	VMS_Moving UMETA(DisplayName = "Moving"),
	VMS_Stopping UMETA(DisplayName = "Stopping")
};
