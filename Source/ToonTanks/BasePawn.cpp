// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxComponent;
	
	//Pancerz czołgu
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(BoxComponent);

	//Wieża
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	//Spawner pocisków przeciwpancernych
	RocketSpawner = CreateDefaultSubobject<USceneComponent>(TEXT("Racket Spawner"));
	RocketSpawner->SetupAttachment(TurretMesh);
}
void ABasePawn::HandleDestruction()
{
	if(DeathParticle)
	{
	UGameplayStatics::SpawnEmitterAtLocation(this , DeathParticle , GetActorLocation(), GetActorRotation());
	}
	if(DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this , DeathSound,GetActorLocation());
	}
}
	
	void ABasePawn::RotateTurret(FVector LookAtTarget)
{
    FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f,ToTarget.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(
	FMath::RInterpTo(TurretMesh->GetComponentRotation(),
	LookAtRotation,
	UGameplayStatics::GetWorldDeltaSeconds(this),
	SpeedRotation)
	);

}



