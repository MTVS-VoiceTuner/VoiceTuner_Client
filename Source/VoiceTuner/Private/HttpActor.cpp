// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpActor.h"
#include "HttpModule.h"
#include "JsonParseLib.h"
#include "LoginUI.h"

// Sets default values
AHttpActor::AHttpActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHttpActor::BeginPlay()
{
	Super::BeginPlay();
	if ( LoginUIFactory ) {
		LoginUI = CreateWidget<ULoginUI>(GetWorld() , LoginUIFactory);
		if ( LoginUI ) {
			LoginUI->AddToViewport();
			auto* pc = GetWorld()->GetFirstPlayerController();
			if ( pc ) {
				pc->bShowMouseCursor = true;

				FInputModeUIOnly InputMode;
				pc->SetInputMode(InputMode);
			}
		}
	}
}

// Called every frame
void AHttpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHttpActor::LoginRequest()
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	req->SetURL(serverURL);
	req->SetVerb(TEXT("POST"));
	req->SetHeader(TEXT("content-type") , TEXT("application/json"));

	req->OnProcessRequestComplete().BindUObject(this , &AHttpActor::ResLoginRequest);

	req->ProcessRequest();
}

void AHttpActor::ResLoginRequest(FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully)
{
	if ( bConnectedSuccessfully ) {
		token = UJsonParseLib::TokenJsonParse(Response->GetContentAsString());
	}
	else {
		UE_LOG(LogTemp , Warning , TEXT("Failed"));
	}
}

