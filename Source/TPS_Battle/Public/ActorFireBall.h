// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorFireBall.generated.h"

UCLASS()
class TPS_BATTLE_API AActorFireBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorFireBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = FireBallSettings)
		class USphereComponent* sphereComp;

	UPROPERTY(EditAnywhere, Category = FireBallSettings)
		class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category = FireBallSettings)
		class UProjectileMovementComponent* movementComp;


	UFUNCTION()
		void OnFireBallOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
