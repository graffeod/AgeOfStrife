// Fill out your copyright notice in the Description page of Project Settings.

#include "AgeOfStrife.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "BaseVehicleAI.h"

ABaseVehicleAI::ABaseVehicleAI() {

}

void ABaseVehicleAI::BeginPlay() {
	Super::BeginPlay();
}

void ABaseVehicleAI::MoveToLocation(FVector location, bool isRollingStop)
{
	RollingStop = isRollingStop;
	Destination = location;
	Distance = GetDistanceFromDestination();
	Started = this->GetWorld()->GetTimeSeconds();
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
	UKismetSystemLibrary::K2_SetTimer(this, "UpdateMovement", .03, true);
}

float ABaseVehicleAI::CalculateSteering() {
	float yawToDestination = CalculateYawToDestination();
	float normalizedMapValue = UKismetMathLibrary::MapRangeUnclamped(CalculateYawToDestination(), -180, 180, -1, 1);
	bool isBetweenRange = UKismetMathLibrary::InRange_FloatFloat(yawToDestination, -90, 90);
	float shortestAngle = 0;
	if(isBetweenRange) {
		shortestAngle = normalizedMapValue;
	}
	float retVal = shortestAngle;//before seeing if going straight is a shorter path.
	if(!isBetweenRange == GetDistanceFromDestination()<1000){
		//do nothing, shortestAngle is correct;
	}
	else {
		shortestAngle = normalizedMapValue;
	}
	if(retVal == 0) {
		retVal = -1;
	}
	else {
		retVal = shortestAngle;//after seeing if going straight is a shorter path.
	}
	return retVal;
}

float ABaseVehicleAI::CalculateYawToDestination() {
	FRotator rotationOfDestination = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Destination);
	FRotator rotationToDestination = UKismetMathLibrary::NormalizedDeltaRotator(rotationOfDestination, this->GetActorRotation());
	return rotationToDestination.Yaw;
}

float ABaseVehicleAI::CalculateThrottle() {
	float retVal = GetDistanceFromDestination() / Distance;
	float inertia = (Distance * .0000025) + 1;
	inertia = FMath::Pow(inertia, this->GetWorld()->GetTimeSeconds() - Started);
	float throttle = inertia * retVal;
	bool accelerating = false;
	if(UKismetMathLibrary::InRange_FloatFloat(CalculateYawToDestination(),-90,90)) {
		accelerating = true;
	}
	throttle = throttle * accelerating ? 1 : -1;
	if(retVal < (RollingStop ? .5 : .6)) {
		retVal = throttle;
	}
	else {
		retVal = accelerating ? 1 : -1;
	}
	return retVal;
}

float ABaseVehicleAI::GetDistanceFromDestination() {
	return (this->GetActorLocation() - Destination).Size();
}

void ABaseVehicleAI::UpdateMovement() {
	float steering = CalculateSteering();
	float throttle = CalculateThrottle();
	GetVehicleMovementComponent()->SetSteeringInput(steering);
	GetVehicleMovementComponent()->SetThrottleInput(throttle);
	if(GetDistanceFromDestination() < 250) {
		GetVehicleMovementComponent()->SetHandbrakeInput(true);
		State = EVehicleMovementState::VMS_Stopping;
		OnMoveCompleted.Broadcast();
		State = EVehicleMovementState::VMS_Idle;
		UKismetSystemLibrary::K2_SetTimer(this, "UpdateMovement", 0.0, false);
	}
	else {
		State = EVehicleMovementState::VMS_Moving;
	}
}
