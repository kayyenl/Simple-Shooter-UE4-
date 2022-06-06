// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_PlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

UBTS_PlayerLocation::UBTS_PlayerLocation() 
{
    NodeName = "Update Player Location";
}

void UBTS_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn == nullptr) {return;}
    OwnerComp.GetBlackboardComponent() -> SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn -> GetActorLocation());
}

