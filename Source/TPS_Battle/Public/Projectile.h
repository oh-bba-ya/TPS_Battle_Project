// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TPS_BATTLE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, Category = BulletSettings)
		class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, Category = BulletSettings)
		class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category = BulletSettings)
		class UProjectileMovementComponent* movementComp;

	UPROPERTY(EditAnywhere, Category = BulletSettings)
		int32 Speed = 2000;

	UPROPERTY(EditAnywhere, Category = BulletSettings)
		float destroyBulletTime = 5.0f;

	UPROPERTY(EditAnywhere, Category = BulletSettings)
		float explosionTime = 3.0f;

	UPROPERTY(EditAnywhere, Category = BulletSettings)
		bool isGrenadeBullet = false;

	UPROPERTY(EditAnywhere, Category = BulletSettings)
		float explosionRange = 400;

	UPROPERTY(EditAnywhere, Category = BulletSettings)
		class UParticleSystem* grenadeImpact;

	UFUNCTION()
		void OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void DestoryBullet();

	void DestoryTimeBullet();

	void Explosion();
	
	void ExplosionTimer();

	bool OnDisTanceToPlayer();

	UPROPERTY(EditAnywhere, Category = BulletSettings)
	class UParticleSystem* Tracer;

	class UParticleSystemComponent* TracerComp;


	class ABaseCharacter* player;



};
