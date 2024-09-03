// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUI.h"
#include "Components/Button.h"
#include "HttpActor.h"

void ULoginUI::NativeConstruct()
{
	LoginButton->OnClicked.AddDynamic(this,&ULoginUI::OnMyButtonClicked);
}

void ULoginUI::OnMyButtonClicked()
{
	HttpActor->OpenKakaoLoginPage();
	HttpActor->LoginRequest();
	RemoveFromParent();
}

