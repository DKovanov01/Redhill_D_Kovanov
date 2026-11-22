// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorActor.h"
#include "Components/BoxComponent.h"

// Sets default values
ADoorActor::ADoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Create our Default Components
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = Door;
	
	// Setting up collision box was originally done for debug, getting rid of it now breaks copilation so I won't mess 
	// with it. Functionality of OnComponentBeginOverlap that was used for debugging has been fully removed;
	DoorProxVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorProximityVolume"));
	DoorProxVolume->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimeline"));
}

// Called when the game starts or when spawned
void ADoorActor::BeginPlay()
{
	Super::BeginPlay();

	//If we have a float curve, bind it's graph to our update function
	if (DoorCurve)
	{
		FOnTimelineFloat ProgressFunction;
		ProgressFunction.BindUFunction(this, FName("UpdateDoor"));

		DoorTimeline->AddInterpFloat(DoorCurve, ProgressFunction);
		DoorTimeline->SetPlayRate(AnimationSpeed); // Setting door opening speed;
	}	
}

void ADoorActor::UpdateDoor(float Value)
{
	FRotator Rotation = FRotator(0.0f, 1 * Value, 0.0f); // 1 => -90 degrees;

	Door->SetRelativeRotation(Rotation);
}

void ADoorActor::ActivateDoor()
{
	if (DoorTimeline->IsPlaying()) // Is the timeline already playing / is the door already opening?
	{
		return; // If yes, return;
	}
	if (DoorTimeline->GetPlaybackPosition() < DoorTimeline->GetTimelineLength()) // Door closed? Open;
	{
		DoorTimeline->Play();
	}
	else if (DoorTimeline->GetPlaybackPosition() > 0.0f) // Door opened? Close;
	{
		DoorTimeline->Reverse();
	}
}