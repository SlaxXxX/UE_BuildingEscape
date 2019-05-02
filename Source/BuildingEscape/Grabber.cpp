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
}

// Grabs shit
void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab it like Gilles"))

		const AActor* grabActor = FindGrabActor();
	if (grabActor)
	{

	}
}

// Releases shit
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Drop it like it's hot"))
}

const AActor* UGrabber::FindGrabActor()
{
	FVector POVlocation;
	FRotator POVrotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(POVlocation, POVrotation);
	FVector LineTraceEnd = POVlocation + POVrotation.Vector() * GrabbingRange;

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(HitResult, POVlocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody));

	return HitResult.GetActor();
}

