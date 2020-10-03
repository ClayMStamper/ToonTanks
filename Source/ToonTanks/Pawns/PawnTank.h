// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()

private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UCameraComponent* Camera;

	FVector MoveDir;
	FQuat RotDir;
	float CurrentSprintBonus = 0.f;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 200.f;
	UPROPERTY(EditAnywhere)
	float MaxSprintBonus = 100.f;
	UPROPERTY(EditAnywhere)
	float RotSpeed = 100.f;
	
	void CalcMoveInput(float Val);
	void CalcRotateInput(float Val);
	void CalcSprintBonus(float Val);

	void Move();
	void Rotate();

public:

	APawnTank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
};
