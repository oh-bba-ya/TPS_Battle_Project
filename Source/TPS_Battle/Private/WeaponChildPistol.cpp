// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponChildPistol.h"
#include "Engine/SkeletalMeshSocket.h"
#include "BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Camera/CameraComponent.h"

AWeaponChildPistol::AWeaponChildPistol()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SetWeaponName(EWeaponName::EWN_Pistol);
}

void AWeaponChildPistol::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<ABaseCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ABaseCharacter::StaticClass()));
	if (player != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Player"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("playerNull"));
	}
	
}

void AWeaponChildPistol::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Pistol Fire"));
	
	const USkeletalMeshSocket* firePosition = GetWeaponMesh()->GetSocketByName(FName("FirePosition"));
	if (firePosition != nullptr) {
		const FVector startPos = firePosition->GetSocketLocation(GetWeaponMesh());;
		
		FRotator startRot = player->GetCamComponent()->GetComponentRotation();
		GetWorld()->SpawnActor<AProjectile>(bulletFactory, startPos,startRot );
	}

}


