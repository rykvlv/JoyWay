#include "Dev/JWDebugDamageSphere.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

AJWDebugDamageSphere::AJWDebugDamageSphere()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
}

void AJWDebugDamageSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJWDebugDamageSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType, {}, this, nullptr, DoFullDamage);
}

