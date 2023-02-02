// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shield.generated.h"

UCLASS()
class TPS_BATTLE_API AShield : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShield();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = ShieldSettings)
		class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = ShieldSettings)
		class USphereComponent* sphereComp;

	UPROPERTY(EditAnywhere, Category = ShieldSettings)
		class UNiagaraComponent* niagaraComp;


	void ActiveShield(float delta);

	void DeactiveShield();

	float currentTime = 0;

};
