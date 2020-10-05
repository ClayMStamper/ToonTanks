// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"

#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

APawnTurret::APawnTurret()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
	 
}

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
    Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!PlayerPawn || CalcDistanceToPlayer() > Range)
        return;
    
    RotateBarrel(PlayerPawn->GetActorLocation());
}

// Called to bind functionality to input
void APawnTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APawnTurret::CheckFireCondition()
{
    // if player == null/dead then return
    if (!PlayerPawn)
    {
        UE_LOG(LogTemp, Error, TEXT("NULL reference to player"));
        return;
    }
    
    //fire if player is in range
    if (CalcDistanceToPlayer() < Range)
        Fire();
}

float APawnTurret::CalcDistanceToPlayer()
{
    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}

void APawnTurret::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}
