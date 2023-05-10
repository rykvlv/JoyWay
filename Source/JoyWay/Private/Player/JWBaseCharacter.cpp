// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/JWBaseCharacter.h"
#include "Camera/CameraComponent.h"

AJWBaseCharacter::AJWBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());
}

void AJWBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJWBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJWBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

