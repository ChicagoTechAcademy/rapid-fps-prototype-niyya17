// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	currentAmmo = maxAmmo;
	storedAmmo = maxAmmo * 2;



}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer())) {
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &APlayerCharacter::Shoot);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Reload);
	}
}

void APlayerCharacter::DecreaseAmmo(int ammoSpent)
{
	currentAmmo -= ammoSpent;
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr) 
	
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("You moved the mouse for looking"));

	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
    {
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}


}

void APlayerCharacter::Jump(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("You pressed a jump button"));
}

void APlayerCharacter::Shoot(const FInputActionValue& Value)
{
	if (currentAmmo > 0)
	{
		// Attempt to fire a projectile.
		if (ProjectileClass)
		{
			// Get the camera transform.
			FVector CameraLocation;
			FRotator CameraRotation;
			GetActorEyesViewPoint(CameraLocation, CameraRotation);

			// Set MuzzleOffset to spawn projectiles slightly in front of the camera.
			MuzzleOffset.Set(100.0f, 50.0f, -50.0f);

			// Transform MuzzleOffset from camera space to world space.
			FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

			// Skew the aim to be slightly upwards.
			FRotator MuzzleRotation = CameraRotation;
			MuzzleRotation.Pitch += 10.0f;

			UWorld* World = GetWorld();
			if (World)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = GetInstigator();

				// Spawn the projectile at the muzzle.
				AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
				if (Projectile)
				{
					// Set the projectile's initial trajectory.
					FVector LaunchDirection = MuzzleRotation.Vector();
					Projectile->FireInDirection(LaunchDirection);
					DecreaseAmmo(1);
				}

			}
		}
	}
}

void APlayerCharacter::Reload(const FInputActionValue& Value)
{

	//if stored ammo = 7, then 7> 5. that works
	//what if stored ammo is 2? 2 !>5, what do we do?
	
	

	while (( currentAmmo < maxAmmo)&& storedAmmo > 0) 
	{
		currentAmmo += 1;
		storedAmmo -= 1;


		UE_LOG(LogTemp, Warning, TEXT("stored Ammo: %d"), storedAmmo);
		UE_LOG(LogTemp, Warning, TEXT("current Ammo: %d"), currentAmmo);
	}

	

}

