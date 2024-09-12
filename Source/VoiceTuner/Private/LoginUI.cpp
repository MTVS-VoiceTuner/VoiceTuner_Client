// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUI.h"
#include "Components/Button.h"
#include "HttpActor.h"
#include "Components/EditableText.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void ULoginUI::NativeConstruct()
{
	HttpActor = Cast<AHttpActor>(UGameplayStatics::GetActorOfClass(GetWorld(), HAFactory));

	LoginButton->OnClicked.AddDynamic(this,&ULoginUI::OnMyButtonClicked);
	TestButton->OnClicked.AddDynamic(this,&ULoginUI::OnMyTestButton);
	TestButton2->OnClicked.AddDynamic(this,&ULoginUI::OnMyTestButton2);

	UserIdPrompt->OnTextCommitted.AddDynamic(this , &ULoginUI::OnMyIDCommitted);

	UserPwdPrompt->OnTextCommitted.AddDynamic(this , &ULoginUI::OnMyPwdCommitted);
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

//	RemoveFromParent();
// 	auto* pc = GetWorld()->GetFirstPlayerController();
// 	if ( pc ) {
// 
// 		FInputModeGameOnly InputMode;
// 		pc->SetInputMode(InputMode);
// 	}
}

void ULoginUI::OnMyTestButton()
{
	HttpActor->SendSoundFileToServer();
}

void ULoginUI::OnMyTestButton2()
{
	HttpActor->SendOriginSoundFileToServer();
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
