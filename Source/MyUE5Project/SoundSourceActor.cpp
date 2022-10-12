// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundSourceActor.h"

#include "AkGameplayStatics.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASoundSourceActor::ASoundSourceActor()
{
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMesh);
	
	AkComponent = CreateDefaultSubobject<UAkComponent>(TEXT("Ak Component"));
	AkComponent->SetupAttachment(RootComponent);
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(AkComponent);
	SphereComponent->SetHiddenInGame(false);

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(RootComponent);
	SplineComponent->SetAutoActivate(false);
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASoundSourceActor::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
}

void ASoundSourceActor::PlayAudioEvent(bool bPlay, bool Debug, const FString& _DebugMessage)
{
	if(AkComponent->AkAudioEvent)
	{
		if(bPlay)
		{
			AkComponent->PostAssociatedAkEvent(0, FOnAkPostEventCallback(), TArray<FAkExternalSourceInfo>());
			
			if (Debug)
			{
				GEngine->AddOnScreenDebugMessage(1, 60.0f, FColor::Green, _DebugMessage);
				GEngine->AddOnScreenDebugMessage(2, 60.0f, FColor::Red, "C++ Implementation");
			}
		}
		else
		{
			AkComponent->Stop();
			ClearOnScreenDebugMessages();
		}
	}
}

void ASoundSourceActor::RotateActorZ(float Delta, float DegreesPerSecond)
{
	const FRotator Rotation = FRotator(0,Delta * DegreesPerSecond,0);
	
	AddActorWorldRotation(Rotation);
}

void ASoundSourceActor::SetFiveSoundPositions(float OffsetY1, float OffsetY2)
{
	TArray OffsetArray = {0.0f, OffsetY1, OffsetY2, OffsetY1 * -1.0f, OffsetY2 * -1.0f};
	TArray<FTransform> Positions;
	int PositionsIndex = 0;

	for(const float Offset : OffsetArray)
	{
		FTransform NewTransform = GetActorTransform();
		const FVector ActorLocation = GetActorLocation();
		
		NewTransform.SetLocation(FVector(ActorLocation.X, ActorLocation.Y + Offset, ActorLocation.Z));
		Positions.Insert(NewTransform, PositionsIndex);
		PositionsIndex++;
	}

	UAkGameplayStatics::SetMultiplePositions(AkComponent, Positions, AkMultiPositionType::MultiSources);
}


void ASoundSourceActor::ClearOnScreenDebugMessages()
{
	GEngine->ClearOnScreenDebugMessages();
}

// Called every frame
void ASoundSourceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

