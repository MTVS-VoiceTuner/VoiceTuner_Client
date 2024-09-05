// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUI.h"
#include "Components/Button.h"
#include "HttpActor.h"
#include "Components/EditableText.h"
#include "Kismet/GameplayStatics.h"

void ULoginUI::NativeConstruct()
{
	HttpActor = Cast<AHttpActor>(UGameplayStatics::GetActorOfClass(GetWorld(), HAFactory));

	LoginButton->OnClicked.AddDynamic(this,&ULoginUI::OnMyButtonClicked);

	UserIdPrompt->OnTextCommitted.AddDynamic(this , &ULoginUI::OnMyIDCommitted);

	UserPwdPrompt->OnTextCommitted.AddDynamic(this , &ULoginUI::OnMyPwdCommitted);
}

void ULoginUI::OnMyButtonClicked()
{
	HttpActor->SendOriginSoundFileToServer();
}

void ULoginUI::OnMyIDCommitted(const FText& Text , ETextCommit::Type CommitMethod)
{
	if ( CommitMethod == ETextCommit::OnEnter || CommitMethod == ETextCommit::OnUserMovedFocus )
	{
		id = Text.ToString();
		UE_LOG(LogTemp , Log , TEXT("User ID: %s") , *id);
	}
}

void ULoginUI::OnMyPwdCommitted(const FText& Text , ETextCommit::Type CommitMethod)
{
	if ( CommitMethod == ETextCommit::OnEnter || CommitMethod == ETextCommit::OnUserMovedFocus )
	{
		pwd = Text.ToString();
		UE_LOG(LogTemp , Log , TEXT("User ID: %s") , *pwd);
	}
}
