// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);
	
	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel Mesh"));
	BarrelMesh->SetupAttachment(BaseMesh);

	// Projectile Spawn Point
	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(BarrelMesh);
	 
}

// Called when the game starts or when spawned
void APawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APawnBase::RotateBarrel(FVector LookTarget)
{
	const FVector BarrelPos = BarrelMesh->GetComponentLocation();
	const FVector SelfToTarget = FVector(LookTarget.X, LookTarget.Y, BarrelPos.Z) - BarrelPos;
	const FRotator NewBarrelRot = FVector(SelfToTarget).Rotation();
	BarrelMesh->SetWorldRotation(NewBarrelRot);
}

void APawnBase::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Fired!"), *GetOwner()->GetName());
}

void APawnBase::HandleDestruction()
{
	// --- Universal --- 
	//play death effects - particles, camera shake, sound

	// --- Child Overrides ---
	// Inform the GameMode
	// -Turret: Destroy self
	// -Tank: Hide() components and stop input
	
}


