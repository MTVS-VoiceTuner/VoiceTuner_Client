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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ULoginUI> LoginUIFactory;

	UPROPERTY()
	class ULoginUI* LoginUI;

	void LoginRequest();

	void ResLoginRequest(FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully);

	void SendSoundFileToServer();

	void ResSendSoundFileToServer(FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully);

	FString serverURL = "http://221.163.19.218:8080/ap";
	FString token;
};
