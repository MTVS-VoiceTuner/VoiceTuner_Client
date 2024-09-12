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
	
	//����� ��û
	UFUNCTION()
	void CreateMySession(FString roomName, int32 playerCount);

	// ����� ����
	UFUNCTION()
	void OnMyCreateSessionComplete(FName SessionName, bool bWasSuccessful);
};
