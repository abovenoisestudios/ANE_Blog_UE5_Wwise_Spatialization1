// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AkComponent.h" // Include this directive to access Ak Component.
#include "Components/SphereComponent.h" // Include this directive to access Sphere Component. 
#include "Components/SplineComponent.h" // Include this directive to access Spline Component.

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundSourceActor.generated.h"

UCLASS()
class MYUE5PROJECT_API ASoundSourceActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundSourceActor();

	#pragma region Wwise Spatialization1 Property Declarations

	/** This actor's static mesh. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio")
	UStaticMeshComponent* StaticMesh;
	/** This actor's Ak Component - Holds and audio event and allows spatialization. */
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Audio")
	UAkComponent* AkComponent;
	
	/** A sphere component to generate overlap events. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio")
	USphereComponent* SphereComponent;
	
	/** A spline will allow this actor to follow the player character's location. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio")
	USplineComponent* SplineComponent;
	
	/** A reference to the player's character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Audio")
	ACharacter* PlayerCharacter;
	
	/** A boolean property to activate debug messages. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio")
	bool bDebug = true;
	
	/** The message to display on screen for debug. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio")
	FString DebugMessage;

	#pragma endregion Wwise Spatialization1 Property Declarations

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	#pragma region Wwise Spatialization1 Function Declarations
	
	/**
	 * @brief Plays or stops the associated event in the AkComponent. Prints a debug message.
	 * @param bPlay true = Play | false = Stop.
	 * @param Debug true = Debug | false = No Debug.
	 * @param _DebugMessage Debug message to print.
	 */
	UFUNCTION(BlueprintCallable, Category="Audio")
	void PlayAudioEvent(bool bPlay, bool Debug, const FString& _DebugMessage);
	
	/**
	 * @brief Rotates the actor on the Z rotator (Yaw).
	 * @param Delta The time difference between the previous frame and the current frame.
	 * @param DegreesPerSecond How many degrees to rotate this actor each second.
	 */
	UFUNCTION(BlueprintCallable, Category="Audio")
	void RotateActorZ(float Delta, float DegreesPerSecond);
	
	/**
	 * @brief Creates five transforms to generate a multi-position sound source.
	 * @param OffsetY1 An offset from the actor's zero vector.
	 * @param OffsetY2 An offset from the actor's zero vector.
	 */
	UFUNCTION(BlueprintCallable, Category="Audio")
	void SetFiveSoundPositions(float OffsetY1, float OffsetY2);

	/** Follow the Player Character's location along the Spline Component.
	 *	Should be called from a Tick function */
	UFUNCTION(BlueprintCallable, Category="Audio")
	void SplineFollowPlayerCharacter();
	
	/** Custom function to clear all debug messages from the screen.
	 *	Exposed to blueprints. */
	UFUNCTION(BlueprintCallable, Category="Audio")
	void ClearOnScreenDebugMessages();

	#pragma endregion Wwise Spatialization1 Function Declarations
	
};
