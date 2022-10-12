// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AkComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SplineComponent.h"

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Audio")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Audio")
	UAkComponent* AkComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Audio")
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Audio")
	USplineComponent* SplineComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Audio")
	ACharacter* PlayerCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio")
	bool bDebug = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio")
	FString DebugMessage;
	
	UFUNCTION(BlueprintCallable, Category="Audio")
	void PlayAudioEvent(bool bPlay, bool Debug, const FString& _DebugMessage);

	UFUNCTION(BlueprintCallable, Category="Audio")
	void RotateActorZ(float Delta, float DegreesPerSecond);

	UFUNCTION(BlueprintCallable, Category="Audio")
	void SetFiveSoundPositions(float OffsetY1, float OffsetY2);
	
	UFUNCTION(BlueprintCallable)
	void ClearOnScreenDebugMessages();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
