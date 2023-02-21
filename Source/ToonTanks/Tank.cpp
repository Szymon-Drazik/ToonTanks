// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"

// Called every frame
void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (TankPlayerController)
    {
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,
                                                     false,
                                                     HitResult);

        ABasePawn::RotateTurret(HitResult.ImpactPoint);
    }
}
void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    GetWorldTimerManager().ClearTimer(FireRateTimerHandle);
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}
ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComponent->SetupAttachment(SpringArm);

    RifleBullet = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet Spawner"));
    RifleBullet->SetupAttachment(TurretMesh);
}
void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
    PlayerInputComponent->BindAction(TEXT("Ammo"), IE_Pressed, this, &ATank::Press);
    PlayerInputComponent->BindAction(TEXT("Ammo"), IE_Released, this, &ATank::Released);
}
// Called when the game starts or when spawned
void ATank::BeginPlay()
{
    Super::BeginPlay();

    TankPlayerController = Cast<APlayerController>(GetController());
}
void ATank::Move(float value)
{
    float Delta = UGameplayStatics::GetWorldDeltaSeconds(this);
    float X = value * Delta * Speed;
    FVector DeltaLocation(0.f);
    DeltaLocation.X = X;
    AddActorLocalOffset(DeltaLocation, true);
}
void ATank::Turn(float value)
{
    float Delta = UGameplayStatics::GetWorldDeltaSeconds(this);
    FRotator DeltaRotation = FRotator::ZeroRotator;
    float Rotation = value * Delta * RotationSpeed;
    DeltaRotation.Yaw = Rotation;
    AddActorLocalRotation(DeltaRotation, true);
}
void ATank::Fire()
{
if(Shoots<1)
{
FVector Location = RocketSpawner->GetComponentLocation();
FRotator Rotation = RocketSpawner->GetComponentRotation();
auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
Projectile->SetOwner(this);
}
Shoots++;
if(Shoots == 1)
{
    GetWorldTimerManager().SetTimer(Delay,[&](){Shoots = 0;},1.5,false);
}
}
void ATank::Press()
{
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATank::Ammo, AmmoTimer, true);
}
void ATank::Released()
{
    GetWorldTimerManager().ClearTimer(FireRateTimerHandle);
}
void ATank::Ammo()
{
    if(AmmoShoots<35)
    {
    FVector RifleLocation = RifleBullet->GetComponentLocation();
    FRotator RifleRotation = RifleBullet->GetComponentRotation();
    auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass2, RifleLocation, RifleRotation);
    Projectile->SetOwner(this);
    }
    AmmoShoots++;
    if(AmmoShoots == 35)
    {
        GetWorldTimerManager().SetTimer(AmmoDelay,[&](){AmmoShoots = 0;},4,false);
    }
}

