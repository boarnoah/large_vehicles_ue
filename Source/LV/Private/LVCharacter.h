// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LVCharacter.generated.h"

UCLASS()
class ALVCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* Mesh3P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	float InteractionDistance = 128.0f;

public:
	ALVCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Val);
	void MoveRight(float Val);
	void ToggleFlying();
	UFUNCTION(Server, Reliable)
	void ServerToggleFlying();
	void FlyUp(float Val);
	void InteractStart();
	UFUNCTION(Server, Reliable)
	void ServerInteractStart();

	bool DoInteractionTrace(FHitResult& hitResult);
};
