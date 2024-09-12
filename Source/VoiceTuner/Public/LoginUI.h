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
	UPROPERTY(meta = ( BindWidget ))
	class UButton* TestButton;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* TestButton2;

	UPROPERTY(meta = (BindWidget))
	class UEditableText* UserIdPrompt;
	
	UPROPERTY(meta = (BindWidget))
	class UEditableText* UserPwdPrompt;

	UFUNCTION()
	void OnMyButtonClicked();
	UFUNCTION()
	void OnMyTestButton();
	UFUNCTION()
	void OnMyTestButton2();

	UPROPERTY()
	class AHttpActor* HttpActor;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AHttpActor> HAFactory;

	UFUNCTION()
	void OnMyIDCommitted(const FText& Text , ETextCommit::Type CommitMethod);
	UFUNCTION()
	void OnMyPwdCommitted(const FText& Text , ETextCommit::Type CommitMethod);

	FString id;
	FString pwd;
};
