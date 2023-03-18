// ProjectZ. All Rights Reserved.


#include "Player/BaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Create a camera boom (pulls in towards the player if there is a collision)
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 400.0f;	
	SpringArmComponent->bUsePawnControlRotation = true;

	// Create a follow camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; 
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetupPlayerSettings();
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Look);
		
		//Running
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &ABaseCharacter::RunTriggered);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Canceled, this, &ABaseCharacter::RunFinished);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &ABaseCharacter::RunFinished);
	}
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	SetupInput();
}

void ABaseCharacter::SetupInput()
{
	if (const auto PlayerController = Cast<APlayerController>(Controller))
	{
		if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ABaseCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ABaseCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ABaseCharacter::RunTriggered()
{
	SetMaxWalkSpeed(RunSpeed);
}

void ABaseCharacter::RunFinished()
{	
	SetMaxWalkSpeed(WalkSpeed);
}

void ABaseCharacter::SetupPlayerSettings()
{
	SetMaxWalkSpeed(WalkSpeed);
}

void ABaseCharacter::SetMaxWalkSpeed(float MaxWalkSpeed)
{
	if(!HasAuthority())
	{
		ServerSetMaxWalkSpeed(MaxWalkSpeed);
	}

	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
}

void ABaseCharacter::ServerSetMaxWalkSpeed_Implementation(float MaxWalkSpeed)
{
	SetMaxWalkSpeed(MaxWalkSpeed);
}

