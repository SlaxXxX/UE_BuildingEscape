// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
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

	if (!PressurePlate)
		UE_LOG(LogTemp, Error, TEXT("%s: NO PRESSURE PLATE"), *GetOwner()->GetName());

	Owner = GetOwner();
}

float UOpenDoor::GetTotalMassOfActorsInTrigger()
{
	if (!PressurePlate)
		return 0.;

	float TotalMass = 0.0f;
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OverlappingActors);

	for (const AActor* Actor : OverlappingActors)
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();

	return TotalMass;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PressurePlate)
		return;

	if (GetTotalMassOfActorsInTrigger() >= MinimumMass)
	{
		TimeDoorCloses = GetWorld()->GetRealTimeSeconds() + DoorCloseTime;
		if (!IsDoorOpen)
		{
			OnOpenRequest.Broadcast();
			IsDoorOpen = true;
		}
	}
	else if (IsDoorOpen && GetWorld()->GetRealTimeSeconds() > TimeDoorCloses)
	{
		OnCloseRequest.Broadcast();
		IsDoorOpen = false;
	}

}

