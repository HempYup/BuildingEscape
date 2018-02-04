// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"

#define OUT

UGrabber::UGrabber() /// Sets default values for this component's properties
{
	PrimaryComponentTick.bCanEverTick = true;	/// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features  off to improve performance if you don't need them.
}

void UGrabber::BeginPlay() /// Called when the game starts
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) /// Called every frame
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!PhysicsHandle) { return; }
	// if the physics handle is attached
	if (PhysicsHandle->GrabbedComponent) { PhysicsHandle->SetTargetLocation(GetLineTracePoints().v2); } /// move the object that we're holding
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();	/// Look for attached input component for Grabbing
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab); /// Bind input
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else { UE_LOG(LogTemp, Warning, TEXT("%s Input Component is missing!"), *GetOwner()->GetName()); }
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();	/// Look for attached physics handle
	if (PhysicsHandle == nullptr) { UE_LOG(LogTemp, Warning, TEXT("%s Physics Handle is missing!"), *GetOwner()->GetName()); }
}

void UGrabber::Grab()
{
	auto HitResult = GetFirstPhysicsBodyInReach(); /// LINE TRACE and see if we reach any actors with physics body collision channel set
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
	if (ActorHit) {	PhysicsHandle->GrabComponentAtLocationWithRotation(
		ComponentToGrab,
		NAME_None,
		ComponentToGrab->GetOwner()->GetActorLocation(),
		ComponentToGrab->GetOwner()->GetActorRotation()); } /// if we hit something, attach a physics handle
}

void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	/// Line-trace (AKA ray-cast) out to reach distance
	FHitResult HitResult;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FTwoVectors TracePoints = GetLineTracePoints();
	GetWorld()->LineTraceSingleByObjectType(OUT HitResult,	TracePoints.v1, TracePoints.v2, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);
	return HitResult;
}

FTwoVectors UGrabber::GetLineTracePoints() const
{
	FVector StartLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(	OUT StartLocation, OUT PlayerViewPointRotation);
	FVector EndLocation = StartLocation + PlayerViewPointRotation.Vector() * Reach;
	return FTwoVectors(StartLocation, EndLocation);
}