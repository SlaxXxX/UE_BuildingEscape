// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();
}

void UOpenDoor::RotateDoor(const float Angle)
{
	FRotator NewRotation = FRotator(0.f, Angle, 0.f);
	Owner->SetActorRotation(NewRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate != nullptr)
	{
		if (PressurePlate->IsOverlappingActor(ActorThatOpens))
		{
			TimeDoorCloses = GetWorld()->GetRealTimeSeconds() + DoorCloseTime;
			if (!IsDoorOpen)
			{
				RotateDoor(OpenAngle);
				IsDoorOpen = true;
			}
		}
		else if (IsDoorOpen && GetWorld()->GetRealTimeSeconds() > TimeDoorCloses)
		{
			RotateDoor(CloseAngle);
			IsDoorOpen = false;
		}

	}

}

