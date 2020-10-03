// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework//SpringArmComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
APawnTank::APawnTank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
    Super::BeginPlay();
	
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    Rotate();
    Move();
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalcMoveInput);
    PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalcRotateInput);
    PlayerInputComponent->BindAxis("Sprint", this, &APawnTank::CalcSprintBonus);
}

void APawnTank::CalcMoveInput(float Val)
{
    const float SpeedMod = MoveSpeed + CurrentSprintBonus;
    MoveDir = FVector(Val * SpeedMod * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APawnTank::CalcRotateInput(float Val)
{
    const float RotAmount = Val * RotSpeed * GetWorld()->DeltaTimeSeconds;
    const FRotator Rotation = FRotator(0, RotAmount, 0);
    RotDir = FQuat(Rotation);
}

void APawnTank::CalcSprintBonus(float Val)
{
    CurrentSprintBonus = Val * MaxSprintBonus;
}

void APawnTank::Move()
{
    AddActorLocalOffset(MoveDir, true);
}

void APawnTank::Rotate()
{
    AddActorLocalRotation(RotDir, true);
}



