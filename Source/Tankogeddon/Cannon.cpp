#include "Cannon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Projectile.h"

ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = sceneComp;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(sceneComp);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);
}

void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();
}

void ACannon::Burst()
{
	if (CurrentBurst == BurstSize)
	{
		GetWorld()->GetTimerManager().ClearTimer(BurstTimer);
		bReadyToFire = true;
		CurrentBurst = 0;
		Shells--;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Shells is: %d"), Shells));
		return;
	}

	CurrentBurst++;

	if (CannonType == ECannonType::FireProjectile)
	{
		FireProjectile();
	}
	else
	{
		FireTrace();
	}
}

void ACannon::FireProjectile()
{
}

void ACannon::FireTrace()
{
}

void ACannon::FireSpecial()
{
	if (!IsReadyToFire() || Shells <= 0)
	{
		return;
    }
	bReadyToFire = false;

	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire projectile")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire trace")));
	}

	GetWorld()->GetTimerManager().SetTimer(BurstTimer, this, &ACannon::Burst, BurstInterval, true, 0.0f);
}

void ACannon::Fire()
{
	if (!IsReadyToFire() || Shells <= 0)
    {
	  return;
    }
	bReadyToFire = false;
	Shells--;

	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire projectile")));
<<<<<<< HEAD
<<<<<<< Updated upstream
=======
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation(), spawnParams);
		if (projectile)
		{
			projectile->Start();
		}
>>>>>>> Stashed changes
=======
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation(), spawnParams);
		{
			projectile->Start();
		}
>>>>>>> Tankogeddon
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire trace")));
		FHitResult hitResult;
		FCollisionQueryParams traceParams;
		traceParams.bTraceComplex = true;
		traceParams.bReturnPhysicalMaterial = false;

		FVector Start = ProjectileSpawnPoint->GetComponentLocation();
		FVector End = Start + ProjectileSpawnPoint->GetForwardVector() * FireRange;

		if (GetWorld()->LineTraceSingleByChannel(hitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel1, traceParams))
		{
			DrawDebugLine(GetWorld(), Start, hitResult.Location, FColor::Purple, false, 1.0f, 0, 5.0f);
			if (hitResult.GetActor())
			{
				//UE_LOG(LogTemp, Warning, TEXT("trace overlap : %s"), *hitResult.GetActor()->GetName());
				hitResult.GetActor()->Destroy();
			}
		}
		else
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 5.0f);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 1 / FireRate, false);
}

void ACannon::Reload()
{
	bReadyToFire = true;
}

bool ACannon::IsReadyToFire()
{
	return bReadyToFire;
}