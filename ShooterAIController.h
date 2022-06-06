// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"


UCLASS()
class THESIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()


public:
	virtual void Tick(float DeltaSeconds) override;
	bool IfDead() const;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* AIBehavior;
	
};
