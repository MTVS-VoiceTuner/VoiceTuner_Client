// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "VTGameInstance.generated.h"

/**
 *
 */
UCLASS()
class VOICETUNER_API UVTGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	void Init();

	void HandleURL(const TArray<FString>& StartUpArguments);

	FString GenerateTokenCallbackURL();
};
