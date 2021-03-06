// Copyright Aaron Grossman 2021

#include "OpenDoor.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;

	CheckForPressurePlate();
	FindAudioComponent();
}

void UOpenDoor::CheckForPressurePlate()
{
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has the OpenDoor component, but no PressurePlate is set!"), *GetOwner()->GetName());
	}
}

void UOpenDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("No UAudioComponent on %s!"), *GetOwner()->GetName());
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PressurePlate)
	{
		return;
	}

	// Only open the door if the mass of the actors is greater than the required mass
	if (TotalMassOfActors() > MassToOpen)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, OpenAngle, DeltaTime, DoorOpenInterpSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	if (!AudioComponent)
	{
		return;
	}

	if (PlayOpenSound)
	{
		PlayOpenSound = false;
		PlayCloseSound = true;
		AudioComponent->Play();
	}
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, OpenAngle - 90.f, DeltaTime, DoorCloseInterpSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	if (!AudioComponent)
	{
		return;
	}
	
	if (PlayCloseSound)
	{
		PlayCloseSound = false;
		PlayOpenSound = true;
		AudioComponent->Play();
	}
}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;

	if (!PressurePlate)
	{
		return TotalMass;
	}

	// Find all overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	
	// Add up all of their masses
	for (AActor* Actor : OverlappingActors)
	{
		UPrimitiveComponent* PrimComponent = Actor->FindComponentByClass<UPrimitiveComponent>();

		if (PrimComponent)
		{
			TotalMass += PrimComponent->GetMass();
		}
	}

	return TotalMass;
}

