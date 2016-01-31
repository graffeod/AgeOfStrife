// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/WheeledVehicle.h"
#include "BaseVehicle.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class AGEOFSTRIFE_API ABaseVehicle : public AWheeledVehicle
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseVehicle")
		float Health = 100;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "BaseVehicle")
		bool IsDead = false;

	virtual void SetIsDead();

	UFUNCTION(BlueprintCallable, Category = "BaseVehicle")
		virtual void CalculateHealth(float delta);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& propertyChangedEvent)
		override;
#endif
	
public:
	// Sets default values for this character's properties
	ABaseVehicle();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	
	
};
