// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginUI.generated.h"

/**
 *
 */
UCLASS()
class VOICETUNER_API ULoginUI : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;

	UPROPERTY(meta = ( BindWidget ))
	class UButton* LoginButton;

	UFUNCTION()
	void OnMyButtonClicked();

	UPROPERTY()
	class AHttpActor* HttpActor;

	void OpenKakaoLoginPage();
};
