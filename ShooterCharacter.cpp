// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "MyGun.h"
#include "Components/CapsuleComponent.h"
#include "TheSimpleShooterGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();	

	Health = MaxHealth;

	Gun = GetWorld() -> SpawnActor<AMyGun>(GunClass);
	GetMesh() -> HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun -> AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun -> SetOwner(this); 
}

bool AShooterCharacter::IfDead() const
{
	if (Health <= 0)	
	{
		return true;
	}
	else 
	{
		return false;
	}
}

float AShooterCharacter::GetHealthPercent() const
{
	return (Health/MaxHealth);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent -> BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent -> BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent -> BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent -> BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent -> BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent -> BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent -> BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);
	PlayerInputComponent -> BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) 
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageApplied = FMath::Min(Health, DamageApplied);
	if (Health > 0)
	{
		Health -= DamageApplied;
	}

	if (IfDead())
	{
		ATheSimpleShooterGameModeBase* GameMode = GetWorld() -> GetAuthGameMode<ATheSimpleShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode -> PawnKilled(this );
		}

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent() -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		
	}
	return DamageApplied;
}

void AShooterCharacter::MoveForward(float AxisValue) 
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue) 
{
	AddControllerPitchInput(LookingRate * 5 * AxisValue * GetWorld() -> GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(float AxisValue) 
{
	AddControllerYawInput(LookingRate  * AxisValue * GetWorld() -> GetDeltaSeconds());
}

void AShooterCharacter::Shoot() 
{
	Gun -> PullTrigger();
}