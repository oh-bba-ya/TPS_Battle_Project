// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponChildShotgun.h"
#include "Engine/SkeletalMeshSocket.h"
#include "BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"


void AWeaponChildShotgun::BeginPlay()
{
	Super::BeginPlay();

	SetWeaponName(EWeaponName::EWN_ShotGun);

	SetFireDelay(1.5f);

}

void AWeaponChildShotgun::Fire(const FVector& HitTarget)
{
	Super::Fire(HitTarget);
	UE_LOG(LogTemp, Warning, TEXT("Shotgun Fire"));

	const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName(FName("MuzzleFlash"));

	if (MuzzleFlashSocket) {
		FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());

		FVector Start = SocketTransform.GetLocation();
		for (int32 i = 0; i < NumberOfPellets; i++) {
			FVector End = TraceEndWithScatter(Start, HitTarget);
			if (bulletFactory != NULL) {
				GetWorld()->SpawnActor<AProjectile>(bulletFactory, SocketTransform.GetLocation(), End.Rotation());
			}
		}
	}
}

FVector AWeaponChildShotgun::TraceEndWithScatter(const FVector& TraceStart, const FVector& HitTarget) {
	FVector ToTargetNormalized = (HitTarget - TraceStart).GetSafeNormal();
	FVector SphereCenter = TraceStart + ToTargetNormalized * DistanceToSphere;
	FVector RandVec = UKismetMathLibrary::RandomUnitVector() * FMath::FRandRange(0.f, SphereRadius);
	FVector EndLoc = SphereCenter + RandVec;
	FVector ToEndLoc = EndLoc - TraceStart;

	DrawDebugSphere(GetWorld(), SphereCenter, SphereRadius, 12, FColor::Red, false,1.0f);
	DrawDebugSphere(GetWorld(), EndLoc, 4.f, 12, FColor::Orange, false,1.0f);
	DrawDebugLine(GetWorld(),
		TraceStart,
		FVector(TraceStart + ToEndLoc * GetTraceLength() / ToEndLoc.Size()),
		FColor::Cyan,
		false,
		1.0f
	);
	
	
	return FVector(TraceStart + ToEndLoc * GetTraceLength() / ToEndLoc.Size());
}