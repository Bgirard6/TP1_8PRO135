// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Meteor.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class TP1_8PRO135_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Base spawn interval (average)
	UPROPERTY(EditAnywhere, Category = "Spawn Settings")
	float BaseSpawnInterval = 5.0f;

	// Variance amount (seconds added/subtracted)
	UPROPERTY(EditAnywhere, Category = "Spawn Settings")
	float IntervalVariance = 3.0f;

	TSubclassOf<AActor> EnemyClass;
	FTimerHandle SpawnTimerHandle;
	
	UFUNCTION()
	void SpawnMeteor();
	
	UFUNCTION()
	void ScheduleNextSpawn();
	
	UPROPERTY(EditAnywhere, Category = "Spawn Settings")
	TSubclassOf<AMeteor> MeteorClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* StaticMesh;
};
