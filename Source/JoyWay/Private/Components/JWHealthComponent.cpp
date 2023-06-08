#include "Components/JWHealthComponent.h"


UJWHealthComponent::UJWHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UJWHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);

	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UJWHealthComponent::OnTakeAnyDamage);
	}
}

void UJWHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigateBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld())
		return;

	SetHealth(Health - Damage);

	if (IsDead())
		OnDeath.Broadcast();
}

void UJWHealthComponent::SetHealth(float HealthValue)
{
	Health = FMath::Clamp(HealthValue, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}

bool UJWHealthComponent::TryToAddHealth(float HealthAmount)
{
	if (IsDead() || IsHealthFull())
		return false;

	SetHealth(Health + HealthAmount);
	
	return true;
}

bool UJWHealthComponent::IsHealthFull() const
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}