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
	class UWidgetSwitcher* StartWidgetSwitcher;

	UPROPERTY(meta = ( BindWidget ))
	class UButton* Button_Commit;
	// ===============LoginPanel=====================
	UPROPERTY(meta = ( BindWidget ))
	class UButton* LoginButton;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* TestButton;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* TestButton2;

	UPROPERTY(meta = ( BindWidget ))
	class UEditableText* UserIdPrompt;

	UPROPERTY(meta = ( BindWidget ))
	class UEditableText* UserPwdPrompt;

	UFUNCTION()
	void OnMyButtonClicked();
	UFUNCTION()
	void OnMyTestButton();
	UFUNCTION()
	void OnMyTestButton2();

	UPROPERTY(EditDefaultsOnly)
	class AHttpActor* HttpActor;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AHttpActor> HAFactory;

	UFUNCTION()
	void OnMyIDCommitted(const FText& Text , ETextCommit::Type CommitMethod);
	UFUNCTION()
	void OnMyPwdCommitted(const FText& Text , ETextCommit::Type CommitMethod);

	FString id;
	FString pwd;
	//======================CustomUI======================
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Button_Gender_Man;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Button_Gender_Woman;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Button_Style_1;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Button_Style_2;

	UPROPERTY(meta = ( BindWidget ))
	class UButton* Button_NameInputClear;


	UPROPERTY(meta = ( BindWidget ))
	class UEditableText* ET_UserNamePrompt;


	UPROPERTY(meta = ( BindWidget ))
	class UImage* Img_Man_Style1;
	UPROPERTY(meta = ( BindWidget ))
	class UImage* Img_Man_Style2;
	UPROPERTY(meta = ( BindWidget ))
	class UImage* Img_Woman_Style1;
	UPROPERTY(meta = ( BindWidget ))
	class UImage* Img_Woman_Style2;

	UFUNCTION()
	void OnMyUserNameCommited(const FText& Text , ETextCommit::Type CommitMethod);

	FString userName;

	// 1 : 남자 2 : 여자
	int32 userGender;
	// 1 or 2
	int32 userStyle;

	UFUNCTION()
	void OnMyClearButtonClick();

	UFUNCTION()
	void OnMyGenderMButtonClick();
	UFUNCTION()
	void OnMyGenderWButtonClick();

	UFUNCTION()
	void OnMyStyle1ButtonClick();

	UFUNCTION()
	void OnMyStyle2ButtonClick();
};
