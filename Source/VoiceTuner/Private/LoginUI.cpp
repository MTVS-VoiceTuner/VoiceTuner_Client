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
	OpenKakaoLoginPage();
	HttpActor->LoginRequest();
}

void ULoginUI::OpenKakaoLoginPage()
{
	FString URL = "https://kauth.kakao.com/oauth/authorize?response_type=code&client_id=92b3e5f16e982fe5395ba97c4bdf34f0&redirect_uri=http://192.168.0.25:8080/api/auth/kakao/login";
	FString ErrorMessage;

	FPlatformProcess::LaunchURL(*URL , nullptr , &ErrorMessage);

	if ( !ErrorMessage.IsEmpty() )
	{
		UE_LOG(LogTemp , Warning , TEXT("Failed to launch URL: %s") , *ErrorMessage);
	}
}

