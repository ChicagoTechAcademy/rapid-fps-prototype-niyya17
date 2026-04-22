// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class RAPIDFPS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// In your class definition:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	//jump
	//look
	//shoot
	//reload

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* ReloadAction;

	void Move(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);
	void Jump(const struct FInputActionValue& Value);
	void Shoot(const struct FInputActionValue& Value);
	void Reload(const struct FInputActionValue& Value);
};
