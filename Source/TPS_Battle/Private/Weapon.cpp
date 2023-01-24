// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimationAsset.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values
AWeapon::AWeapon() :
	WeaponState(EWeaponState::EWS_PickUp),
	WeaponName(EWeaponName::EWN_Base)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetupAttachment(RootComponent);
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	PickupWidget->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnSphereOverlap);
	AreaSphere->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnSphereEndOverlap);

	if (PickupWidget != nullptr) {
		PickupWidget->SetVisibility(false);
	}

	player = Cast<ABaseCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ABaseCharacter::StaticClass()));
	if (player == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Weapon Class Player Null"));
	}

}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* baseCharacter = Cast<ABaseCharacter>(OtherActor);
	if (baseCharacter != nullptr) {
		baseCharacter->SetOverlapWeapon(this);
		SetVisibilityWIdget(true);
	}
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ABaseCharacter* baseCharacter = Cast<ABaseCharacter>(OtherActor);
	if (baseCharacter != nullptr) {
		baseCharacter->SetOverlapWeapon(nullptr);
		SetVisibilityWIdget(false);
	}
}

void AWeapon::Fire(const FVector& HitTarget)
{
	// 총애니메이션 재생
	if (FireAnimation) {
		UE_LOG(LogTemp, Warning, TEXT("Weapon Animation"));
		WeaponMesh->PlayAnimation(FireAnimation, false);
	}
}



// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	TraceUnderCrosshairs(HitResult);

}

void AWeapon::TraceUnderCrosshairs(FHitResult& TraceHitResult)
{
	FVector2D ViewportSize;
	if (GEngine && GEngine->GameViewport) {
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}

	FVector2D CrosshairLocation(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);
	FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection;

	// Screen -> World 좌표계 변경
	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(
		UGameplayStatics::GetPlayerController(GetWorld(), 0),
		CrosshairLocation,
		CrosshairWorldPosition,
		CrosshairWorldDirection
	);

	if (bScreenToWorld) {
		FVector Start = CrosshairWorldPosition;

		FVector End = Start + CrosshairWorldDirection * GetTraceLength();

		GetWorld()->LineTraceSingleByChannel(
			TraceHitResult,
			Start,
			End,
			ECollisionChannel::ECC_Visibility
		);

		if (!TraceHitResult.bBlockingHit) {
			TraceHitResult.ImpactPoint = End;
			hitTarget = End;
		}
		else {
			hitTarget = TraceHitResult.ImpactPoint;
			DrawDebugSphere(
				GetWorld(),
				TraceHitResult.ImpactPoint,
				12.f,
				12,
				FColor::Red
			);
		}
	}
}

void AWeapon::SetVisibilityWIdget(bool overlap)
{
	if (PickupWidget != nullptr) {
		PickupWidget->SetVisibility(overlap);
	}

}

