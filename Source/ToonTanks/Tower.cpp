// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Projectile.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(IfInRange())
	{
		ABasePawn::RotateTurret(Tank->GetActorLocation());
	}
}
void ATower::HandleDestruction()
{
Super::HandleDestruction();
if(DeathSound)
{
	UGameplayStatics::PlaySoundAtLocation(this , DeathSound,GetActorLocation());
}
Destroy();

}
void ATower::BeginPlay()
{
Super::BeginPlay();

Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this , 0));

GetWorldTimerManager().SetTimer(FireRateTimerHandle,this,&ATower::CheckFireCondition,Timer,true);
}
void ATower::CheckFireCondition()
{
	if(Tank->bAlive)
	{
		if(IfInRange())
		{
			FireTower();
		}
	}
	
}
bool ATower::IfInRange()
{
if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if(Distance <= FireRange)
		{
			return true;
		}
	}
	return false;
}
void ATower::FireTower()
{
FVector Location = RocketSpawner->GetComponentLocation();
FRotator Rotation = RocketSpawner->GetComponentRotation();
auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
Projectile->SetOwner(this);
}

