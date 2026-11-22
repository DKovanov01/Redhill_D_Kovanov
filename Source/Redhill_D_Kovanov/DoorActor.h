// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "DoorActor.generated.h"

class UCurveFloat;

UCLASS()
class REDHILL_D_KOVANOV_API ADoorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//MeshComponents to represent Door assets
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DoorFrame;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Door;
 
	//BoxComponent which will be used as our Proximity volume.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* DoorProxVolume;
	
	// Variable to hold the Curve asset
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTimelineComponent* DoorTimeline;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	UCurveFloat* DoorCurve;
	
	UPROPERTY(VisibleAnywhere, Category = "Door")
	float OpenAngle = 1.0f; // "Angle" is actually -90 degrees as per attached curve float; Setting this value to more than 1 results in -90 degrees * value, not sure why;
		
	UPROPERTY(EditAnywhere, Category = "Door")
	float AnimationSpeed = 1.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
	bool bIsOpen = false;
	
	UFUNCTION()
	void UpdateDoor(float Value);	

public:	
	UFUNCTION(BlueprintCallable, Category = "Door Actions")
	void ActivateDoor();
};
