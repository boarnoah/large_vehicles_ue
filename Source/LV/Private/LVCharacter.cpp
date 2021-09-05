#include "LVCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ALVCharacter::ALVCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create third person mesh, for visibility in MP
	Mesh3P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh3P"));
	Mesh3P->SetOwnerNoSee(true);
	Mesh3P->SetupAttachment(GetCapsuleComponent());
	Mesh3P->bCastDynamicShadow = true;
	Mesh3P->SetCastShadow(true);
	Mesh3P->SetRelativeRotation(FRotator(0, -90.0f, 0));
	Mesh3P->SetRelativeLocation(FVector(0, 0, -100.0f));
}

// Called when the game starts or when spawned
void ALVCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALVCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ALVCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ALVCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ALVCharacter::StopJumping);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ALVCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALVCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Fly", IE_Pressed, this, &ALVCharacter::ToggleFlying);
	PlayerInputComponent->BindAxis("FlyUp", this, &ALVCharacter::FlyUp);
}

void ALVCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ALVCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ALVCharacter::ToggleFlying()
{
	ServerToggleFlying();
}

void ALVCharacter::ServerToggleFlying_Implementation()
{
	if(GetCharacterMovement()->MovementMode == MOVE_Flying)
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	} else
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	}
}

void ALVCharacter::FlyUp(float Val)
{
	if (GetCharacterMovement()->MovementMode == MOVE_Flying && Val != 0.f)
	{
		AddMovementInput(FVector::UpVector, Val);
	}
}
