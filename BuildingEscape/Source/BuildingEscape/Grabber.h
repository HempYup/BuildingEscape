// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()
public:	
	UGrabber(); /// Sets default values for this component's properties
protected:
	virtual void BeginPlay() override;	/// Called when the game starts
private:
	float Reach = 100.f;
	void FindPhysicsHandleComponent(); /// find attached physics handle component
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
	void Grab(); /// Ray-cast and grab what's in reach
	void Release(); /// Called when grab is released
	void SetupInputComponent(); /// Setup (assumed) attached input component

	// Return hit for first physics body in reach
	FHitResult GetFirstPhysicsBodyInReach() const;
	// Return begin and end of trace
	FTwoVectors GetLineTracePoints() const;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override; /// Called every frame

};
