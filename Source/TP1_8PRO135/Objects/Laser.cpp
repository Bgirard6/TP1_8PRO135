// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Laser.h"

#include "Meteor.h"

// Sets default values
ALaser::ALaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	
	StaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALaser::BeginPlay()
{
	Super::BeginPlay();
	
	StaticMesh->SetCollisionObjectType(ECC_GameTraceChannel1);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	StaticMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	StaticMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	StaticMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	
	StaticMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	
	StaticMesh->SetGenerateOverlapEvents(true);
	StaticMesh->SetSimulatePhysics(false);
		
	
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ALaser::OnOverlapBegin);
	
	Velocity = GetActorForwardVector() * Speed;
	Velocity.Z = 0.0f;
	
	GetWorld()->GetTimerManager().SetTimer(
		DespawnTimerHandle,
		this,
		&ALaser::Despawn,
		DespawnTimer,
		false
	);
	
	
}

// Called every frame
void ALaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector NewLocation = GetActorLocation() + (Velocity * DeltaTime);
	SetActorLocation(NewLocation);

}

void ALaser::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this || OtherActor == GetOwner())
	{
		return;
	}

	if (OtherActor->ActorHasTag(TEXT("Meteor")))
	{
		AMeteor* Meteor = static_cast<AMeteor*>(OtherActor);
		Meteor->LoseHealth();
		GetWorld()->GetTimerManager().ClearTimer(DespawnTimerHandle);
		Destroy();
	}
}

void ALaser::Despawn()
{
	GetWorld()->GetTimerManager().ClearTimer(DespawnTimerHandle);
	Destroy();
}

