// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Ammo();

	public:
	ATank();

	bool bAlive = true ;

	FTimerHandle FireRateTimerHandle;
	
	APlayerController* GetTankPlayerController() const{return TankPlayerController;}	
	bool ifclick;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	private:

	UPROPERTY(EditDefaultsOnly, Category="Combat", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> ProjectileClass;

	void Fire();

	FTimerHandle Delay;

	UPROPERTY(BlueprintReadOnly , meta =(AllowPrivateAccess = "true"))
	int32 Shoots = 0;

	FTimerHandle AmmoDelay;
	UPROPERTY(BlueprintReadOnly , meta =(AllowPrivateAccess = "true"))
	int32 AmmoShoots = 0;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<class AProjectile> ProjectileClass2;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , category ="Czołg" , meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , category ="Czołg" , meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , category ="Czołg" , meta = (AllowPrivateAccess = "true"))
	USceneComponent* RifleBullet;

	void Move(float value);
	void Turn(float value);
	void Press();
	void Released();
	
	UPROPERTY(EditAnywhere, category="FireRate")
	float AmmoTimer = 0.5;
	
	

	UPROPERTY(EditAnywhere, category = "Movement")
	float Speed = 1;

	UPROPERTY(EditAnywhere, category = "Movement")
	float RotationSpeed = 1;

	APlayerController* TankPlayerController;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
