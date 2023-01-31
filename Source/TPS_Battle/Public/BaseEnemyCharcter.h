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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyFSM)
	class UBaseEnemyCharacterFSM* enemyFSM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GunMesh)
	class USkeletalMeshComponent* pistolGunMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GunMesh)
	class UBoxComponent* muzzleBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyWidget)
	class UWidgetComponent* hpWidgetComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyWidget)
	TSubclassOf<class UUserWidget> BP_WidgetEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyWidget)
	class UWidgetEnemy* widgetEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyHP)
	float enemyMaxHP = 15.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyHP)
	float enemyCurHP = 15.0f;

	UFUNCTION()
	void MySelfDestory();

};
