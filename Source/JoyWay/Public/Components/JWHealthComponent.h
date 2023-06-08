#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JWHealthComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JOYWAY_API UJWHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UJWHealthComponent();

	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return FMath::IsNearlyZero(Health); }

	void SetHealth(float HealthValue);

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;

	bool TryToAddHealth(float HealthAmount);
	bool IsHealthFull() const;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100;

private:
	float Health = 0.0f;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigateBy, AActor* DamageCauser);

	
};
