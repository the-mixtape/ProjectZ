// ProjectZ. All Rights Reserved.


#include "Player/EllieCharacter.h"

AEllieCharacter::AEllieCharacter()
{
	HairMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Hair");
	HairMesh->SetupAttachment(GetMesh(), "Hair_Socket");
	
	GlassesMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Glasses");
	GlassesMesh->SetupAttachment(GetMesh());
	GlassesMesh->SetLeaderPoseComponent(GetMesh());
	
	TorsoMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Torso");
	TorsoMesh->SetupAttachment(GetMesh());
	TorsoMesh->SetLeaderPoseComponent(GetMesh());
	
	LegsMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Legs");
	LegsMesh->SetupAttachment(GetMesh());
	LegsMesh->SetLeaderPoseComponent(GetMesh());
	
	ShoesMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Shoes");
	ShoesMesh->SetupAttachment(GetMesh());
	ShoesMesh->SetLeaderPoseComponent(GetMesh());
	
	BackpackMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Backpack");
	BackpackMesh->SetupAttachment(GetMesh());
	BackpackMesh->SetLeaderPoseComponent(GetMesh());
}
