// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileBody;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(EditDefaultsOnly, category="Pocisk")
	float Initial;
	UPROPERTY(EditDefaultsOnly, category="Pocisk")
	float Max;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(EditAnywhere, category = "Particle")
	class UParticleSystem* HitParticle;

	UPROPERTY(EditDefaultsOnly)
	float Damage;

	UPROPERTY(VisibleAnywhere ,category = "Particle")
	class UParticleSystemComponent* ParticleComponent;
	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
