// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpActor.generated.h"

UCLASS()
class VOICETUNER_API AHttpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHttpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame2
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ULoginUI> LoginUIFactory;

	UPROPERTY()
	class ULoginUI* LoginUI;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UCustomizationUI> CustomUIFactory;

	UPROPERTY()
	class UCustomizationUI* CustomUI;



	void LoginRequest(FString id, FString pwd);

	void ResLoginRequest(FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully);
	
	UFUNCTION(BlueprintCallable)
	void SendSoundFileToServer();

	void ResSendSoundFileToServer(FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully); 

	UFUNCTION(BlueprintCallable)
 	void SendOriginSoundFileToServer();
 
 	void ResSendOriginSoundFileToServer(FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully);

	FString serverURL = "http://192.168.0.25:8080/sendBase64";
	FString token = "eyJhbGciOiJIUzI1NiJ9.eyJzdWIiOiIyIiwiYXV0aCI6IlVTRVIiLCJ0eXBlIjoiYWNjZXNzIiwiaWF0IjoxNzI2MTMyNTkwLCJleHAiOjE3MjYxMzM0OTB9.xjw-Bw6P5Fkw8sHjWgJjNR3awznfek3a1zpBi412hNQ";
	FString myID = "shinhonggyu";
	FString myPwd;
	FString song_id = "song_456";
	FString track_id = "track_789";

	FString solution_10;

	FString CurrentLevelName;
};
