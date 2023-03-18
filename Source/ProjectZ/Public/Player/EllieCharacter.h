// ProjectZ. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/BaseCharacter.h"
#include "EllieCharacter.generated.h"


UCLASS()
class PROJECTZ_API AEllieCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEllieCharacter();

#pragma region Components
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	USkeletalMeshComponent* HairMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	USkeletalMeshComponent* GlassesMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	USkeletalMeshComponent* TorsoMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	USkeletalMeshComponent* LegsMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	USkeletalMeshComponent* ShoesMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	USkeletalMeshComponent* BackpackMesh;
#pragma endregion 
};
