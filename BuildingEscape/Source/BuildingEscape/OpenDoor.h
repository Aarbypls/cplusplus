// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;
	void CheckForPressurePlate();
	void FindAudioComponent();

private:

	float InitialYaw;
	float CurrentYaw;
	float DoorLastOpened = 0.f;

	// Tracks whether the sound has been played
	bool PlayOpenSound = true;
	bool PlayCloseSound = false;

	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.f;

	UPROPERTY(EditAnywhere)	
	float DoorCloseDelay = 0.1f;

	UPROPERTY(EditAnywhere)
	float DoorOpenInterpSpeed = 1.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseInterpSpeed = 4.f;

	UPROPERTY(EditAnywhere)
	float MassToOpen = 50.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;
};
