// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResultWIdget.generated.h"

/**
 *
 */
UCLASS()
class VOICETUNER_API UResultWIdget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	class UTextBlock* TB_Score;

	UFUNCTION(BlueprintCallable)
	void SetScore(int32 Score);

};
