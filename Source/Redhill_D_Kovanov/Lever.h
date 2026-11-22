// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lever.generated.h"

class USphereComponent;

UCLASS()
class REDHILL_D_KOVANOV_API ALever : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALever();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	USphereComponent* CollisionSphere;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditInstanceOnly, Category = "Interaction")
	TObjectPtr<AActor> ConnectedDoor = nullptr;;

	// Function to open/close the door, previously 2 different functions;
	UFUNCTION(BlueprintCallable, Category="Interaction")
	void ActivateLever();

};
