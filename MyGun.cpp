// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"


// Sets default values
AMyGun::AMyGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("The Root Component");
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("The Gun Mesh");
	Mesh -> SetupAttachment(Root);

}

void AMyGun::PullTrigger() 
{	
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = GunTrace(Hit, ShotDirection);
	if (bSuccess)
	{
		//DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactFlash, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);
		if (Hit.GetActor())
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			AController* OwningController = GetOwnerController();
			Hit.GetActor() -> TakeDamage(Damage, DamageEvent, OwningController, this);
			//UE_LOG(LogTemp, Warning, TEXT("You have hit %s!"), *(Hit.GetActor() -> GetName()));
		}
	}
}

// Called when the game starts or when spawned
void AMyGun::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AMyGun::GunTrace(FHitResult& Hit, FVector& ShotDirection) 
{	
	AController* OwningController = GetOwnerController(); 
	if (OwningController == nullptr) {return false;}
	FVector VPLocation; 
	FRotator VPRotation;
	OwningController -> GetPlayerViewPoint(VPLocation, VPRotation);

	FVector End = VPLocation + VPRotation.Vector() * MaxRange;

	//DrawDebugCamera(GetWorld(), VPLocation , VPRotation , 90.f, 2, FColor::Red, true);

	Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	ShotDirection = - VPRotation.Vector();
	return GetWorld() -> LineTraceSingleByChannel(Hit, VPLocation, End, ECC_GameTraceChannel1, Params);
}

AController* AMyGun::GetOwnerController() const
{
	APawn* OwningPawn = Cast<APawn>(GetOwner());
	if (!OwningPawn) {return nullptr;}
	return OwningPawn -> GetController();
}

