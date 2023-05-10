// Fill out your copyright notice in the Description page of Project Settings.


#include "JWGameModeBase.h"
#include "Player/JWBaseCharacter.h"
#include "Player/JWPlayerController.h"


AJWGameModeBase::AJWGameModeBase() 
{
	DefaultPawnClass = AJWBaseCharacter::StaticClass();
	PlayerControllerClass = AJWPlayerController::StaticClass();
}