// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseVehicle.h"
#include "VehicleMovementStateEnum.h"
#include "BaseVehicleAI.generated.h"

/**
 * 
 */
UCLASS()
class AGEOFSTRIFE_API ABaseVehicleAI : public ABaseVehicle
{
	GENERATED_BODY()
		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBaseVehicleAIMoveCompleted);
	
public:
	UPROPERTY(BlueprintAssignable, Category = "BaseVehicleAI")
		FBaseVehicleAIMoveCompleted OnMoveCompleted;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseVehicleAI")
		FVector Destination = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseVehicleAI")
		float Distance = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseVehicleAI")
		float Started = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseVehicleAI")
		bool RollingStop = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseVehicleAI")
		EVehicleMovementState State = EVehicleMovementState::VMS_Idle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseVehicleAI")
		FTimerHandle timerUpdateMovement;

	UFUNCTION(BlueprintCallable, Category = "BaseVehicleAI")
		virtual void MoveToLocation(FVector location, bool isRollingStop);

	UFUNCTION(BlueprintCallable, Category = "BaseVehicleAI")
		virtual void UpdateMovement();

	UFUNCTION(BlueprintCallable, Category = "BaseVehicleAI")
		virtual float CalculateSteering();

	UFUNCTION(BlueprintCallable, Category = "BaseVehicleAI")
		virtual float CalculateThrottle();

	UFUNCTION(BlueprintCallable, Category = "BaseVehicleAI")
		virtual float GetDistanceFromDestination(); 

	UFUNCTION(BlueprintCallable, Category = "BaseVehicleAI")
		virtual float CalculateYawToDestination();

public:
	// Sets default values for this character's properties
	ABaseVehicleAI();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
