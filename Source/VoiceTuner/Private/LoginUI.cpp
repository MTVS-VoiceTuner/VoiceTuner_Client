// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUI.h"
#include "Components/Button.h"
#include "HttpActor.h"
#include "Components/EditableText.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "HSW_NetGameInstance.h"
#include "Components/WidgetSwitcher.h"

void ULoginUI::NativeConstruct()
{
	HttpActor = Cast<AHttpActor>(UGameplayStatics::GetActorOfClass(GetWorld() , HAFactory));

	LoginButton->OnClicked.AddDynamic(this , &ULoginUI::OnMyButtonClicked);

	Button_NameInputClear->OnClicked.AddDynamic(this , &ULoginUI::OnMyClearButtonClick);

	UserIdPrompt->OnTextCommitted.AddDynamic(this , &ULoginUI::OnMyIDCommitted);

	UserPwdPrompt->OnTextCommitted.AddDynamic(this , &ULoginUI::OnMyPwdCommitted);

	ET_UserNamePrompt->OnTextCommitted.AddDynamic(this , &ULoginUI::OnMyUserNameCommited);

	Button_Gender_Man->OnClicked.AddDynamic(this , &ULoginUI::OnMyGenderMButtonClick);
	Button_Gender_Woman->OnClicked.AddDynamic(this , &ULoginUI::OnMyGenderWButtonClick);

	Button_Style_1->OnClicked.AddDynamic(this , &ULoginUI::OnMyStyle1ButtonClick);
	Button_Style_2->OnClicked.AddDynamic(this , &ULoginUI::OnMyStyle2ButtonClick);

	Button_Commit->OnClicked.AddDynamic(this , &ULoginUI::OnMyCommitButtonClick);
}

void ULoginUI::OnMyButtonClicked()
{
	UserIdPrompt->SetText(FText());
	UserPwdPrompt->SetText(FText());
	if ( !id.IsEmpty() && !pwd.IsEmpty() ) {
		HttpActor->LoginRequest(id , pwd);
	}
	else {
		UserIdPrompt->SetUserFocus(GetWorld()->GetFirstPlayerController());
		UserIdPrompt->SetKeyboardFocus();
	}
	StartWidgetSwitcher->SetActiveWidgetIndex(1);
}

void ULoginUI::OnMyIDCommitted(const FText& Text , ETextCommit::Type CommitMethod)
{
	if ( CommitMethod == ETextCommit::OnEnter || CommitMethod == ETextCommit::OnUserMovedFocus )
	{
		id = Text.ToString();
	}
}

void ULoginUI::OnMyPwdCommitted(const FText& Text , ETextCommit::Type CommitMethod)
{
	if ( CommitMethod == ETextCommit::OnEnter || CommitMethod == ETextCommit::OnUserMovedFocus )
	{
		pwd = Text.ToString();
	}
}

void ULoginUI::OnMyUserNameCommited(const FText& Text , ETextCommit::Type CommitMethod)
{
	if ( CommitMethod == ETextCommit::OnEnter || CommitMethod == ETextCommit::OnUserMovedFocus )
	{
		userName = Text.ToString();
	}
}

void ULoginUI::OnMyClearButtonClick()
{
	ET_UserNamePrompt->SetText(FText::FromString(""));
}

void ULoginUI::OnMyGenderMButtonClick()
{
	userGender = 1;
	Button_Gender_Woman->SetBackgroundColor(FLinearColor(FVector3d(0.612992f , 0.651344f , 0.791667f)));
	Button_Gender_Man->SetBackgroundColor(FLinearColor(FVector3d(0.75f , 0.0f , 0.8f)));
}

void ULoginUI::OnMyGenderWButtonClick()
{
	userGender = 2;
	Button_Gender_Man->SetBackgroundColor(FLinearColor(FVector3d(0.612992f , 0.651344f , 0.791667f)));
	Button_Gender_Woman->SetBackgroundColor(FLinearColor(FVector3d(0.75f , 0.0f , 0.8f)));
}

void ULoginUI::OnMyStyle1ButtonClick()
{
	userStyle = 1;

	Button_Style_2->SetBackgroundColor(FLinearColor(FVector3d(0.612992f , 0.651344f , 0.791667f)));
	Button_Style_1->SetBackgroundColor(FLinearColor(FVector3d(0.75f , 0.0f , 0.8f)));
}

void ULoginUI::OnMyStyle2ButtonClick()
{
	userStyle = 2;

	Button_Style_1->SetBackgroundColor(FLinearColor(FVector3d(0.612992f , 0.651344f , 0.791667f)));
	Button_Style_2->SetBackgroundColor(FLinearColor(FVector3d(0.75f , 0.0f , 0.8f)));
}

void ULoginUI::OnMyCommitButtonClick()
{
	HttpActor->gi->SetGender(userGender);
	HttpActor->gi->SetStyle(userStyle);
	HttpActor->gi->SetName(userName);

	FName LobbyLevelName = "HSW_Alpha_Stage";
	UGameplayStatics::OpenLevel(this , LobbyLevelName);
}
