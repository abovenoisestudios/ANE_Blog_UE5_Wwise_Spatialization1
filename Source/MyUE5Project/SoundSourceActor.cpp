// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundSourceActor.h"


#include "GameFramework/Character.h" // Include this directive to access ACharacter functions.
#include "AkGameplayStatics.h" // Include this directive to access Wwise functions.
#include "Kismet/GameplayStatics.h" // Include this directive to access the GetPlayerCharacter() function.

// Sets default values
ASoundSourceActor::ASoundSourceActor()
{
	#pragma region Wwise Spatialization1 Constructor Implementation

	// Creates a Static Mesh Component.
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMesh); // Sets this Static Mesh as the actor's Root Component.

	// Creates an Ak Component.
	AkComponent = CreateDefaultSubobject<UAkComponent>(TEXT("Ak Component"));
	AkComponent->SetupAttachment(RootComponent); // Attaches this Ak Component to the Root Component.
	
	// Creates a Sphere Component.
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(AkComponent); // Attaches this Spline Component to the Ak Component.
	SphereComponent->SetHiddenInGame(false); // Sets this component visibility in gameplay.

	// Creates a Spline Component.
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(RootComponent); // Attaches this Spline Component to the Root Component.
	SplineComponent->SetAutoActivate(false); // Initializes this component De-activated. Its activated on the "BP_SplineSoundSourceActor" class.

	#pragma endregion Wwise Spatialization1 Constructor Implementation
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASoundSourceActor::BeginPlay()
{
	Super::BeginPlay();

	// Gets a reference of the player character. Inherited to all child classes.
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
}

// Called every frame
void ASoundSourceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#pragma region Wwise Spatialization1 Function Implementations

void ASoundSourceActor::PlayAudioEvent(bool bPlay, bool Debug, const FString& _DebugMessage)
{
	if(AkComponent->AkAudioEvent) // Continue if there is an Ak Audio Event assigned.
	{
		if(bPlay) // Continue if bPlay = true.
		{
			// Play the associated Ak Audio Event.
			AkComponent->PostAssociatedAkEvent(0, FOnAkPostEventCallback(), TArray<FAkExternalSourceInfo>());
			
			if (Debug) // Prints debug messages if Debug = true.
			{
				GEngine->AddOnScreenDebugMessage(1, 60.0f, FColor::Green, _DebugMessage);
				GEngine->AddOnScreenDebugMessage(2, 60.0f, FColor::Red, "C++ Implementation");
			}
		}
		else // Stops the Ak Audio Event and clears all Debug messages if bPlay = false.
		{
			AkComponent->Stop();
			ClearOnScreenDebugMessages();
		}
	}
}

void ASoundSourceActor::RotateActorZ(float Delta, float DegreesPerSecond)
{
	// Creates a new Rotation multiplying the Delta time to DegreesPerSecond in the Y (Yaw) Rotator.
	const FRotator Rotation = FRotator(0,Delta * DegreesPerSecond,0);
	
	AddActorWorldRotation(Rotation); // Adds the new Rotator to this actor.
}

void ASoundSourceActor::SetFiveSoundPositions(float OffsetY1, float OffsetY2)
{
	// An array of float Offsets.
	TArray OffsetsArray{
						0.0f, // Actors location + No Offset.
						OffsetY1, // Actors location + Offset 1.
						OffsetY2, // Actors location + Offset 2.
						OffsetY1 * -1.0f, // Actors location + negative Offset 1.
						OffsetY2 * -1.0f}; // Actors location + negative Offset 2.
	
	TArray<FTransform> PositionsArray; // An empty array of Transforms.

	for(const float Offset : OffsetsArray) // A for loop to iterate over the OffsetsArray values.
	{
		FTransform NewTransform = GetActorTransform(); // Gets this actor's transform.
		const FVector ActorLocation = GetActorLocation(); // Gets this actor's location.

		// Sets the NewTransform location adding each offset from the OffsetArray.
		NewTransform.SetLocation(FVector(ActorLocation.X, ActorLocation.Y + Offset, ActorLocation.Z));
		PositionsArray.Add(NewTransform); // Adds the NewTransform to the PositionsArray.
	}

	// Uses the PositionsArray to set multiple positions for this AK Component.
	UAkGameplayStatics::SetMultiplePositions(AkComponent, PositionsArray, AkMultiPositionType::MultiSources);
}

void ASoundSourceActor::SplineFollowPlayerCharacter()
{
	if(SplineComponent->IsActive()) // Continue if the Spline Component is active.
	{
		// Gets the closest Player Character's Location along the Spline Component.
		const FVector PlayerCharacterLocation = SplineComponent->FindLocationClosestToWorldLocation
		(PlayerCharacter->GetActorLocation(), ESplineCoordinateSpace::World);

		// Sets the Ak Component to this new location along the Spline Component.
		// The Sphere Component is attached to the Ak Component, so it will move too.
		AkComponent->SetWorldLocation(PlayerCharacterLocation);
	}
	else // If the Spline Component is not active, prints a Debug message.
	{
		GEngine->AddOnScreenDebugMessage(3, 10.0f, FColor::Red, "Spline Component is not active");
	}
}

void ASoundSourceActor::ClearOnScreenDebugMessages()
{
	GEngine->ClearOnScreenDebugMessages(); // Clear any existing debug messages.
}

#pragma region Wwise Spatialization1 Function Implementations


