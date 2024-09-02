// Fill out your copyright notice in the Description page of Project Settings.


#include "VTGameInstance.h"

void UVTGameInstance::Init()
{
	Super::Init();

	FCoreDelegates::ApplicationReceivedStartupArgumentsDelegate.AddUObject(this , &UVTGameInstance::HandleURL);

}

FString UVTGameInstance::GenerateTokenCallbackURL()
{
	FString BaseURL = TEXT("mygame://auth/callback");
	FString TokenParam = TEXT("token=");

	FString FinalURL = FString::Printf(TEXT("%s?%s") , *BaseURL , *TokenParam);
	return FinalURL;
}

void UVTGameInstance::HandleURL(const TArray<FString>& StartUpArguments)
{
	for ( const FString& Arg : StartUpArguments ) {
		if ( Arg.StartsWith(GenerateTokenCallbackURL()) ) {
			FString Token;

			if ( FParse::Value(*Arg , TEXT("token=") , Token) ) {
				UE_LOG(LogTemp , Log , TEXT("Token Valid : %s") , *Token);
			}
		}
	}
}
