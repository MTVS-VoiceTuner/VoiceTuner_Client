// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpActor.h"
#include "HttpModule.h"
#include "JsonParseLib.h"
#include "LoginUI.h"
#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"

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
		if ( LoginUI && !loginOnce ) {
			loginOnce = true;
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

void AHttpActor::LoginRequest(FString id , FString pwd)
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	myID = id;
	myPwd = pwd;

	req->SetURL("http://39.115.91.53:8080/api/auth/login");
	req->SetVerb(TEXT("POST"));
	req->SetHeader(TEXT("content-type") , TEXT("application/json"));
	req->SetContentAsString(UJsonParseLib::MakeLoginInfoJson(id , pwd));

	req->OnProcessRequestComplete().BindUObject(this , &AHttpActor::ResLoginRequest);

	req->ProcessRequest();
}

void AHttpActor::ResLoginRequest(FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully)
{
	if ( bConnectedSuccessfully ) {
		token = UJsonParseLib::TokenJsonParse(Response->GetContentAsString());
		LoginUI->RemoveFromParent();
		auto* pc = GetWorld()->GetFirstPlayerController();
		if ( pc ) {
			pc->bShowMouseCursor = false;

			FInputModeGameOnly InputMode;
			pc->SetInputMode(InputMode);
		}
	}
	else {
		UE_LOG(LogTemp , Warning , TEXT("Failed"));
	}
}

void AHttpActor::SendSoundFileToServer()
{
	UE_LOG(LogTemp , Warning , TEXT("SendGradingDataToServer"));
	TArray<uint8> FileData;
	FString FilePath = FPaths::ProjectSavedDir() + TEXT("/BouncedWavFiles/Sinhodeong_CUT.wav");

	if ( FFileHelper::LoadFileToArray(FileData , *FilePath) )
	{
		UE_LOG(LogTemp , Log , TEXT("File loaded successfully: %s") , *FilePath);
	}
	else
	{
		UE_LOG(LogTemp , Error , TEXT("Failed to load file: %s") , *FilePath);
		return;
	}

	FString En_SoundFile = FBase64::Encode(FileData);

	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	req->SetURL("http://39.115.91.53:8888/sendBase64");
	req->SetVerb("POST");
	req->SetHeader(TEXT("User-Agent") , "UnrealEngine/5.0");
	req->SetHeader(TEXT("token") , FString::Printf(TEXT("%s") , *token));
	req->SetHeader(TEXT("content-type") , TEXT("application/json"));
	req->SetContentAsString(UJsonParseLib::MakeSoundFileDate(myID , FString::Printf(TEXT("%s") , *song_id) , FString::Printf(TEXT("%s") , *track_id) , 0.0 , 10.0 , En_SoundFile));

	req->OnProcessRequestComplete().BindUObject(this , &AHttpActor::ResSendSoundFileToServer);

	req->ProcessRequest();
}

void AHttpActor::ResSendSoundFileToServer(FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully)
{
	if ( bConnectedSuccessfully ) {
		solution_10 = UJsonParseLib::ReturnJsonParse(Response->GetContentAsString());
		FString FilePath = FPaths::ProjectContentDir() + TEXT("solution_10.txt");
		if ( FFileHelper::SaveStringToFile(solution_10 , *FilePath) )
		{
			UE_LOG(LogTemp , Warning , TEXT("save success : %s") , *FilePath);
		}
		else
		{
			UE_LOG(LogTemp , Error , TEXT("save success : %s") , *FilePath);
		}
	}
	else {
		UE_LOG(LogTemp , Warning , TEXT("Failed"));
	}
}

void AHttpActor::SendOriginSoundFileToServer()
{
	TArray<uint8> FileData;
	FString FilePath = FPaths::ProjectSavedDir() + TEXT("/BouncedWavFiles/Sinhodeong.wav");
	if ( !FFileHelper::LoadFileToArray(FileData , *FilePath) )
	{
		UE_LOG(LogTemp , Error , TEXT("Failed to load file: %s") , *FilePath);
		return;
	}
	else {
		UE_LOG(LogTemp , Verbose , TEXT("Successed to load file: %s") , *FilePath);
	}

	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	req->SetURL("http://192.168.0.25:8080/ppt/compare_similarity");
	req->SetVerb("POST");
	req->SetHeader(TEXT("User-Agent") , "UnrealEngine/5.0");
	req->SetHeader(TEXT("token") , FString::Printf(TEXT("%s") , *token));
	req->SetHeader(TEXT("content-type") , TEXT("multipart/form-data"));
	req->SetContent(FileData);

	req->OnProcessRequestComplete().BindUObject(this , &AHttpActor::ResSendSoundFileToServer);

	req->ProcessRequest();
	UE_LOG(LogTemp , Warning , TEXT("SendOriginSoundFileToServer(), ProcessRequest()"));
}

void AHttpActor::ResSendOriginSoundFileToServer(FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully)
{
	if ( bConnectedSuccessfully ) {
		solution = UJsonParseLib::ReturnJsonParse(Response->GetContentAsString());
		FString FilePath = FPaths::ProjectContentDir() + "solution.txt";
		if ( FFileHelper::SaveStringToFile(solution , *FilePath) )
		{
			UE_LOG(LogTemp , Warning , TEXT("파일 저장 성공: %s") , *FilePath);
		}
		else
		{
			UE_LOG(LogTemp , Error , TEXT("파일 저장 실패: %s") , *FilePath);
		}
	}
	else {
		UE_LOG(LogTemp , Warning , TEXT("Failed"));
	}
}



