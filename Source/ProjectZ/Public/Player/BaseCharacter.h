// ProjectZ. All Rights Reserved.	

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BaseCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;


UENUM(BlueprintType)
enum class ELocomotionState : uint8
{
	ELS_Idle UMETA(DisplayName="Idle"),
	ELS_Walk UMETA(DisplayName="Walk"),
	ELS_Run UMETA(DisplayName="Run"),
};


UCLASS()
class PROJECTZ_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

#pragma region Components
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;
#pragma endregion

#pragma region PlayerSettings
protected:
	UPROPERTY(EditDefaultsOnly, Category = "PlayerSettings|Speed")
	float WalkSpeed = 175.f;

	UPROPERTY(EditDefaultsOnly, Category = "PlayerSettings|Speed")
	float RunSpeed = 300.f;
#pragma endregion 
	
	
public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

#pragma region Input
private:
	void SetupInput();
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	/** Run Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RunAction;
	

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for looking input */
	void RunTriggered();

	/** Called for looking input */
	void RunFinished();
#pragma endregion

private:
	void SetupPlayerSettings();
	
	void SetMaxWalkSpeed(float InSpeed);

	UFUNCTION(Server, Reliable)
	void ServerSetMaxWalkSpeed(float InSpeed);

public:
	UPROPERTY(Replicated, BlueprintReadOnly)
	FVector InputVector;

	UPROPERTY(Replicated, BlueprintReadOnly)
	float MaxWalkSpeed;

private:
	void UpdateReplicateVariables();

	void SetInputVector(FVector InVector);

	UFUNCTION(Server, Reliable)
	void SetServerInputVector(FVector InVector);

};
