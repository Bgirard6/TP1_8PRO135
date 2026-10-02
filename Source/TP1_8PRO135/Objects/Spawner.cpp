// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Spawner.h"

#include "Components/SphereComponent.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	
	StaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
	ScheduleNextSpawn();
	
	
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::SpawnMeteor()
{
	
	UClass* classToSpawn = MeteorClass ? MeteorClass.Get() : AMeteor::StaticClass();
	
	FVector location = GetActorLocation();
	
	GetWorld()->SpawnActor<AMeteor>(classToSpawn, location, FRotator::ZeroRotator);
	
	ScheduleNextSpawn();
}

void ASpawner::ScheduleNextSpawn()
{
	float minTimeToSpawn = FMath::Min(0.f, BaseSpawnInterval-IntervalVariance);
	float maxTimeToSpawn = BaseSpawnInterval+IntervalVariance;
	
	float timeToSpawn = FMath::RandRange(minTimeToSpawn, maxTimeToSpawn);
	
	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&ASpawner::SpawnMeteor,
		timeToSpawn,
		false // NOT looping
	);
}

