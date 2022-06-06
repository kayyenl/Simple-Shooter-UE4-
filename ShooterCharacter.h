// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AMyGun;

UCLASS()
class THESIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintPure) //same and better than blueprnt callable. Blueprint pure nodes like this does not change any global parameters or state.
	bool IfDead() const; //const often goes with blueprintpure.

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	void Shoot();

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	UPROPERTY(EditAnywhere)
	float LookingRate = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "GUN TYPE")
	TSubclassOf<AMyGun> GunClass;

	UPROPERTY()
	AMyGun* Gun;

	UPROPERTY(EditDefaultsOnly, Category = "HEALTH")
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "HEALTH")
	float Health;
};
