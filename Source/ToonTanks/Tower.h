// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
	public:

	void HandleDestruction();
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly, category="Tower Range")
	float FireRange;

	protected:

	virtual void BeginPlay() override ;

	private:

	UPROPERTY(EditDefaultsOnly, Category="Combat", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> ProjectileClass;

	void FireTower();

	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditAnywhere, category="FireRate")
	float Timer = 2.f;

	void CheckFireCondition();
	class ATank* Tank;
	bool IfInRange();
};
