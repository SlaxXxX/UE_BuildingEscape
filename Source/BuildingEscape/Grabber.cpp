// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/EngineTypes.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PhysicsHandle->SetTargetLocation(GetGrabLocation());
}

// Grabs shit
void UGrabber::Grab()
{
	UPrimitiveComponent* grabComponent = FindGrabComponent();
	if (grabComponent)
	{
		PhysicsHandle->GrabComponent(grabComponent, NAME_None, grabComponent->GetOwner()->GetActorLocation(), true);
	}
}

// Releases shit
void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}

UPrimitiveComponent* UGrabber::FindGrabComponent()
{
	FVector POVlocation;
	FRotator POVrotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(POVlocation, POVrotation);

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(HitResult, POVlocation, GetGrabLocation(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody));

	return HitResult.GetComponent();
}

FVector UGrabber::GetGrabLocation()
{
	FVector POVlocation;
	FRotator POVrotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(POVlocation, POVrotation);
	return POVlocation + POVrotation.Vector() * GrabbingRange;
}

