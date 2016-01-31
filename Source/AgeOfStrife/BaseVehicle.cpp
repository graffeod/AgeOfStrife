// Fill out your copyright notice in the Description page of Project Settings.

#include "AgeOfStrife.h"
#include "BaseVehicle.h"

ABaseVehicle::ABaseVehicle() {
	
}

void ABaseVehicle::BeginPlay() {
	Super::BeginPlay();
}

void ABaseVehicle::CalculateHealth(float delta) {
	Health += delta;
	SetIsDead();
}

void ABaseVehicle::SetIsDead() {
	if(Health <= 0) {
		IsDead = true;
	}
	else {
		IsDead = false;
	}
}

#if WITH_EDITOR
void ABaseVehicle::PostEditChangeProperty(FPropertyChangedEvent& propertyChangedEvent) {
	IsDead = false;
	Health = 100;
	Super::PostEditChangeProperty(propertyChangedEvent);
}
#endif