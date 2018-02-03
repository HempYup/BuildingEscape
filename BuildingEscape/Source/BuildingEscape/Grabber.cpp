// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
//#include "DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay() /// Called when the game starts
{
	Super::BeginPlay();
	/*UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));*/
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();	/// Look for attached physics handle
	if (PhysicsHandle) { UE_LOG(LogTemp, Warning, TEXT("%s Physics Handle is found!"), *GetOwner()->GetName()); }
	else { UE_LOG(LogTemp, Warning, TEXT("%s Physics Handle is missing!"), *GetOwner()->GetName()); }
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"));
	// LINE TRACE and see if we reach any actors with physics body collision channel set
	GetFirstPhysicsBodyInReach();
	// if we hit something
		// attach a physics handle
	// TODO attach physics
}
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"));
	// TODO release physics handle
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();	/// Look for attached input component for Grabbing
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Input Component is found!"), *GetOwner()->GetName());
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab); /// Bind input
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else { UE_LOG(LogTemp, Warning, TEXT("%s Input Component is missing!"), *GetOwner()->GetName()); }
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	/*UE_LOG(LogTemp, Warning, TEXT("PlayerViewPointLocation = %s. PlayerViewPointRotation = %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());*/

	FVector LineTraceDirection = PlayerViewPointRotation.Vector();
	FVector LineTraceEnd = PlayerViewPointLocation + (LineTraceDirection * Reach);

	/*DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0, 2.0f);*/

	FHitResult LineTraceHit;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(OUT LineTraceHit, PlayerViewPointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);
	AActor* ActorHit = LineTraceHit.GetActor();
	if (ActorHit) { UE_LOG(LogTemp, Warning, TEXT("LineTraceHit is hitting: %s"), *(ActorHit->GetName())); }
	return FHitResult();
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) /// Called every frame
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// if the physics handle is attached
		// move the object that we're holding
	// get player view point this tick



}

