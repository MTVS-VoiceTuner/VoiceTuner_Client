// Fill out your copyright notice in the Description page of Project Settings.


#include "HSW_NetGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

void UHSW_NetGameInstance::Init()
{
	auto* subSystem = IOnlineSubsystem::Get();
	if ( subSystem )
	{
		SessionInterface = subSystem->GetSessionInterface();

		//방 생성 요청 -> 응답
		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UHSW_NetGameInstance::OnMyCreateSessionComplete);
	}
}

void UHSW_NetGameInstance::CreateMySession(FString roomName , int32 playerCount)
{
	FOnlineSessionSettings settings;

	// 1. 전용서버를 사용하는가?
	settings.bIsDedicated = false; // 아니요.

	// 2. 랜선(로컬,Lan)으로 매치를 하는가?
	FName subsysName = IOnlineSubsystem::Get()->GetSubsystemName(); // Null이면 로컬.
	settings.bIsLANMatch = subsysName == "NULL";

	// 3. 매칭이 공개(true)냐, 비공개(false, 초대를 통해서 매칭)냐.
	settings.bShouldAdvertise = true;

	// 4. 유저의 상태 정보(온라인/자리비움/등등) 사용 여부
	settings.bUsesPresence = true;

	// 5. 중간에 난입 가능한가?
	settings.bAllowJoinInProgress = true;
	settings.bAllowJoinViaPresence = true;

	// 6. 최대 인원수
	settings.NumPublicConnections = playerCount;

	// 7. 커스텀 정보
	settings.Set(FName("ROOM_NAME") , roomName , EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	settings.Set(FName("HOST_NAME") , MySessionName , EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	FUniqueNetIdPtr netID = GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().GetUniqueNetId();

	SessionInterface->CreateSession(*netID , FName(MySessionName) , settings);
}

void UHSW_NetGameInstance::OnMyCreateSessionComplete(FName SessionName , bool bWasSuccessful)
{
	if ( bWasSuccessful )
	{
	}
	else
	{
	}
}
