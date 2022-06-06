// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerx.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void APlayerControllerx::BeginPlay() 
{
    HUD = CreateWidget(this, HUDClass);
    if (HUD != nullptr)
    {
        HUD -> AddToViewport();
    }
}

void APlayerControllerx::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) 
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    HUD -> RemoveFromViewport();

    //UE_LOG(LogTemp, Warning, TEXT("Game Has Ended!!"));
    if (bIsWinner)
    {
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        if (WinScreen != nullptr)
        {
            WinScreen -> AddToViewport();
        }
    }
    else
    {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
        if (LoseScreen != nullptr)
        {
            LoseScreen -> AddToViewport();
        }
    }

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

