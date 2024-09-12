// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineSessionInterface.h"
#include "HSW_NetGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class VOICETUNER_API UHSW_NetGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	IOnlineSessionPtr SessionInterface;

	FString MySessionName = TEXT("LukasHan");
	
	//规积己 夸没
	UFUNCTION()
	void CreateMySession(FString roomName, int32 playerCount);

	// 规积己 览翠
	UFUNCTION()
	void OnMyCreateSessionComplete(FName SessionName, bool bWasSuccessful);
};
