// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();


	void HandleDestruction();

	UPROPERTY(EditAnyWhere, category="TurretRotation")
	float SpeedRotation;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , category ="Czołg" , meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , category ="Czołg" , meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , category ="Czołg" , meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , category ="Czołg" , meta = (AllowPrivateAccess = "true"))
	USceneComponent* RocketSpawner;

	UPROPERTY(EditAnywhere, category = "Death")
	class UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere , category="Sound") 
	class USoundBase* DeathSound;
	
	private:
	
	protected:

	void RotateTurret(FVector LookAtTarget);
	
};
