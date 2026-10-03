// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Meteor.h"

#include "Spawner.h"
#include "TP1_8PRO135Character.h"
#include "TP1_8PRO135PlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMeteor::AMeteor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	
	StaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMeteor::BeginPlay()
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
	
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &AMeteor::OnOverlapBegin);
	
	ATP1_8PRO135Character* player = Cast<ATP1_8PRO135Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (player)
	{
		Velocity = player->GetActorLocation() - GetActorLocation();
		Velocity.Normalize();
		Velocity *= FMath::RandRange(MinSpeed, MaxSpeed);
		Velocity.Z = 0;
	}
	
	GetWorld()->GetTimerManager().SetTimer(
		DespawnTimerHandle,
		this,
		&AMeteor::Despawn,
		DespawnTimer,
		true
	);
	
	health = FMath::RandRange(1, 5);
}

// Called every frame
void AMeteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + (Velocity * DeltaTime);
	SetActorLocation(NewLocation);
}

void AMeteor::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherActor != GetOwner() && OtherActor->ActorHasTag(TEXT("Player")))
	{
		ATP1_8PRO135Character* Player = static_cast<ATP1_8PRO135Character*>(OtherActor);
		Player->LoseHealth();
		GetWorld()->GetTimerManager().ClearTimer(DespawnTimerHandle);
		Destroy();
	}
}

void AMeteor::Despawn()
{
	GetWorld()->GetTimerManager().ClearTimer(DespawnTimerHandle);
	Destroy();
}

void AMeteor::LoseHealth()
{
	health -= 1;
	
	if (health <= 0)
	{
		ATP1_8PRO135Character* player = Cast<ATP1_8PRO135Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (player)
		{
			pla
		}
		Destroy();
	}
}

