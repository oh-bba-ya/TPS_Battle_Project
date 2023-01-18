// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemyCharcter.generated.h"

UCLASS()
class TPS_BATTLE_API ABaseEnemyCharcter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemyCharcter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//class UCapsuleComponent* capsuleComp;
	//class UStaticMeshComponent* MeshComp;
	//class USceneComponent* sceneComp;

	int32 GetEnemyHP();
	void SetEnemyHP(int32 hp);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSMComponent)
	class UBaseEnemyCharacterFSM* fsm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GunMesh)
	class USkeletalMeshComponent* pistolMeshComp;

private:
	int32 enemyHP = 100;

};
