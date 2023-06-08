#include "Weapon/JWLauncherWeapon.h"
#include "Weapon/JWLauncherProjectileActor.h"
#include "Kismet/GameplayStatics.h"

void AJWLauncherWeapon::StartFire()
{
	MakeShot();
}

void AJWLauncherWeapon::MakeShot()
{
	if (!GetWorld())
		return;

	FVector TraceStart;
	FVector TraceEnd;
	GetTraceData(TraceStart, TraceEnd);

	FHitResult HitResult;

	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	AJWLauncherProjectileActor* Projectile = GetWorld()->SpawnActorDeferred<AJWLauncherProjectileActor>(ProjectileClass, SpawnTransform);
	if (Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}
}

