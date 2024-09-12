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

		//�� ���� ��û -> ����
		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UHSW_NetGameInstance::OnMyCreateSessionComplete);
	}
}

void UHSW_NetGameInstance::CreateMySession(FString roomName , int32 playerCount)
{
	FOnlineSessionSettings settings;

	// 1. ���뼭���� ����ϴ°�?
	settings.bIsDedicated = false; // �ƴϿ�.

	// 2. ����(����,Lan)���� ��ġ�� �ϴ°�?
	FName subsysName = IOnlineSubsystem::Get()->GetSubsystemName(); // Null�̸� ����.
	settings.bIsLANMatch = subsysName == "NULL";

	// 3. ��Ī�� ����(true)��, �����(false, �ʴ븦 ���ؼ� ��Ī)��.
	settings.bShouldAdvertise = true;

	// 4. ������ ���� ����(�¶���/�ڸ����/���) ��� ����
	settings.bUsesPresence = true;

	// 5. �߰��� ���� �����Ѱ�?
	settings.bAllowJoinInProgress = true;
	settings.bAllowJoinViaPresence = true;

	// 6. �ִ� �ο���
	settings.NumPublicConnections = playerCount;

	// 7. Ŀ���� ����
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
