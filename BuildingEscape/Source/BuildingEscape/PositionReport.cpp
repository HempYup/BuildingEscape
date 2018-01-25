// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	FString ObjectName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Position report for %s"), *ObjectName);


	// UE_LOG(LogTemp, Warning, TEXT("Position report reporting for duty on Chair!")); 
	// Logs, Printing Messages to yourself during runtime (UE4 Wiki Tutorial)
	//UE_LOG is a macro.
	//Log coloring goes like this: Log(GREY COLOR) = Log | Log(YELLOW) = Warning | Log(RED) = Error. Here we are using Warning.
	//TEXT is another macro, which takes in a string.
	
	
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

